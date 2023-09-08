#include "Window.h"
HWND g_hWnd;
DWORD g_dwWindowWidth;
DWORD g_dwWindowHeight;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

bool Window::SetRegisterClassWindow(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; //���������ν��� �����̺�Ʈ->�޼���ť ����
    wcex.hInstance = hInstance;
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));// (COLOR_WINDOW + 1);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.lpszClassName = L"������";
    WORD ret = RegisterClassExW(&wcex);

    return true;
}

bool Window::SetWindow(const WCHAR* szTitle, DWORD dwWindowWidth, DWORD dwWindowHeight)
{
    g_dwWindowWidth = m_dwWindowWidth = dwWindowWidth;
    g_dwWindowHeight = m_dwWindowHeight = dwWindowHeight;
    m_dwWindowPosX = 1920 / 2 - dwWindowWidth / 2;
    m_dwWindowPosY = 1080 / 2 - dwWindowHeight / 2;

#ifndef _DEBUG
    m_dwExStyle = WS_EX_TOPMOST;
    m_dwStyle = WS_POPUPWINDOW;
#else
    m_dwExStyle = WS_EX_APPWINDOW;
#endif
    m_hWnd = CreateWindowEx(
        m_dwExStyle,
        L"������",
        szTitle,
        m_dwStyle,
        m_dwWindowPosX, m_dwWindowPosY,
        m_dwWindowWidth, m_dwWindowHeight,
        nullptr,
        nullptr,
        m_hInstance,
        nullptr);

    if (!m_hWnd)
    {
        return FALSE;
    }
    g_hWnd = m_hWnd;
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    return true;
}