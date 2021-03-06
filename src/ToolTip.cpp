﻿// MIT License
// Copyright (C) August 2016 Hotride

#include "ToolTip.h"
#include "SelectedObject.h"
#include "Managers/FontsManager.h"
#include "Managers/ConfigManager.h"
#include "Managers/MouseManager.h"
#include "Managers/ClilocManager.h"
#include "Renderer/RenderAPI.h"
#include "Utility/PerfMarker.h"

extern RenderCmdList *g_renderCmdList;

CToolTip g_ToolTip;

CToolTip::CToolTip()
{
}

CToolTip::~CToolTip()
{
    Reset();
}

void CToolTip::Reset()
{
    m_TextSprite.Clear();
    m_Object = nullptr;
}

void CToolTip::Create(CTextSprite &textSprite, const wstr_t &str, int &width, int minWidth)
{
    g_FontManager.SetUseHTML(true);
    g_FontManager.RecalculateWidthByInfo = true;
    textSprite.Clear();
    auto font = (uint8_t)g_ConfigManager.ToolTipsTextFont;
    if (width == 0)
    {
        width = g_FontManager.GetWidthW(font, str);
        if (width > 600)
        {
            width = 600;
        }

        width = g_FontManager.GetWidthExW(font, str, width, TS_CENTER, UOFONT_BLACK_BORDER);
        if (width > 600)
        {
            width = 600;
        }
    }

    if (width < minWidth)
    {
        width = minWidth;
    }

    g_FontManager.GenerateW(
        font,
        textSprite,
        str,
        g_ConfigManager.ToolTipsTextColor,
        5,
        width,
        TS_CENTER,
        UOFONT_BLACK_BORDER);

    g_FontManager.RecalculateWidthByInfo = false;
    g_FontManager.SetUseHTML(false);
}

void CToolTip::Set(const wstr_t &str, int maxWidth)
{
    if (str.length() == 0u)
    {
        return;
    }

    Use = !(Timer > g_Ticks);
    CRenderObject *object = g_SelectedObject.Object;
    if (object == m_Object || object == nullptr)
    { //Уже забиндено или нет объекта для бинда
        return;
    }

    Timer = g_Ticks + g_ConfigManager.ToolTipsDelay;
    m_Object = object;
    Use = false;
    Data = str;
    ClilocID = 0;
    MaxWidth = maxWidth;
    Position.X = 0;
    Position.Y = 0;

    Create(m_TextSprite, Data, MaxWidth, 0);
}

void CToolTip::Set(int clilocID, const astr_t &str, int maxWidth, bool toCamelCase)
{
    Set(g_ClilocManager.Cliloc(g_Language)->GetW(clilocID, toCamelCase, str), maxWidth);
    ClilocID = clilocID;
}

void CToolTip::Draw(int cursorWidth, int cursorHeight)
{
    ScopedPerfMarker(__FUNCTION__);

    if (!Use /*|| !g_ConfigManager.UseToolTips*/)
    {
        return;
    }

    if (m_TextSprite.Empty())
    {
        Create(m_TextSprite, Data, MaxWidth, 0);
    }

    if (!m_TextSprite.Empty())
    {
        int x = Position.X;
        int y = Position.Y;
        if (x == 0)
        {
            x = g_MouseManager.Position.X - (m_TextSprite.Width + 8);
        }

        if (y == 0)
        {
            y = g_MouseManager.Position.Y - (m_TextSprite.Height + 8);
        }

        if (y < 0)
        {
            y = Position.Y;
            //y = g_MouseManager.Position.Y + cursorHeight;
        }

        if (x < 0)
        {
            x = Position.X;
            //x = g_MouseManager.Position.X + cursorWidth;
        }

        m_TextSprite.Draw_Tooltip(x, y, m_TextSprite.Width + 8, m_TextSprite.Height + 8);
    }
    Use = false;
}
