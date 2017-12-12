/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#include "StdAfx.h"
#include "CharacterTrack.h"

#define LOOP_TRANSITION_TIME 1.0f

//////////////////////////////////////////////////////////////////////////
bool CCharacterTrack::Serialize(XmlNodeRef& xmlNode, bool bLoading, bool bLoadEmptyTracks)
{
    if (bLoading)
    {
        xmlNode->getAttr("AnimationLayer", m_iAnimationLayer);
    }
    else
    {
        xmlNode->setAttr("AnimationLayer", m_iAnimationLayer);
    }

    return TAnimTrack<ICharacterKey>::Serialize(xmlNode, bLoading, bLoadEmptyTracks);
}

void CCharacterTrack::SerializeKey(ICharacterKey& key, XmlNodeRef& keyNode, bool bLoading)
{
    if (bLoading)
    {
        const char* str;

        str = keyNode->getAttr("anim");
        cry_strcpy(key.m_animation, str);

        key.m_duration = 0;
        key.m_endTime = 0;
        key.m_startTime = 0;
        key.m_bLoop = false;
        key.m_bBlendGap = false;
        key.m_bInPlace = false;
        key.m_speed = 1;
        keyNode->getAttr("length", key.m_duration);
        keyNode->getAttr("end", key.m_endTime);
        keyNode->getAttr("speed", key.m_speed);
        keyNode->getAttr("loop", key.m_bLoop);
        keyNode->getAttr("blendGap", key.m_bBlendGap);
        keyNode->getAttr("unload", key.m_bUnload);
        keyNode->getAttr("inplace", key.m_bInPlace);
        keyNode->getAttr("start", key.m_startTime);
    }
    else
    {
        if (strlen(key.m_animation) > 0)
        {
            keyNode->setAttr("anim", key.m_animation);
        }
        if (key.m_duration > 0)
        {
            keyNode->setAttr("length", key.m_duration);
        }
        if (key.m_endTime > 0)
        {
            keyNode->setAttr("end", key.m_endTime);
        }
        if (key.m_speed != 1)
        {
            keyNode->setAttr("speed", key.m_speed);
        }
        if (key.m_bLoop)
        {
            keyNode->setAttr("loop", key.m_bLoop);
        }
        if (key.m_bBlendGap)
        {
            keyNode->setAttr("blendGap", key.m_bBlendGap);
        }
        if (key.m_bUnload)
        {
            keyNode->setAttr("unload", key.m_bUnload);
        }
        if (key.m_bInPlace)
        {
            keyNode->setAttr("inplace", key.m_bInPlace);
        }
        if (key.m_startTime != 0)
        {
            keyNode->setAttr("start", key.m_startTime);
        }
    }
}

void CCharacterTrack::GetKeyInfo(int key, const char*& description, float& duration)
{
    assert(key >= 0 && key < (int)m_keys.size());
    CheckValid();
    description = 0;
    duration = 0;
    if (strlen(m_keys[key].m_animation) > 0)
    {
        description = m_keys[key].m_animation;
        if (m_keys[key].m_bLoop)
        {
            float lastTime = m_timeRange.end;
            if (key + 1 < (int)m_keys.size())
            {
                lastTime = m_keys[key + 1].time;
            }
            // duration is unlimited but cannot last past end of track or time of next key on track.
            duration = lastTime - m_keys[key].time;
        }
        else
        {
            if (m_keys[key].m_speed == 0)
            {
                m_keys[key].m_speed = 1.0f;
            }
            duration = m_keys[key].GetActualDuration();
        }
    }
}

float CCharacterTrack::GetKeyDuration(int key) const
{
    assert(key >= 0 && key < (int)m_keys.size());
    const float EPSILON = 0.001f;
    if (m_keys[key].m_bLoop)
    {
        float lastTime = m_timeRange.end;
        if (key + 1 < (int)m_keys.size())
        {
            // EPSILON is required to ensure the correct ordering when getting nearest keys.
            lastTime = m_keys[key + 1].time + std::min(LOOP_TRANSITION_TIME,
                    GetKeyDuration(key + 1) - EPSILON);
        }
        // duration is unlimited but cannot last past end of track or time of next key on track.
        return std::max(lastTime - m_keys[key].time, 0.0f);
    }
    else
    {
        return m_keys[key].GetActualDuration();
    }
}