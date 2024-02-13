#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
int clickCount = 0;
bool messageBoxDisplayed = false;
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg)
    {
        case WM_LBUTTONDOWN:
            if (!messageBoxDisplayed) {
                clickCount++;
                InvalidateRect(hwnd, NULL, TRUE);
                if (clickCount == 100) {
                    messageBoxDisplayed = true;
                    int msgboxID = MessageBox(
                        NULL,
                        (LPCSTR)"You have reached 100 clicks. Would you like to reset the extractor?",
                        (LPCSTR)"Quantum Radeon Energy Extractor",
                        MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2
                    );
                    switch (msgboxID) {
                    case IDYES:
                        clickCount = 0;
                        messageBoxDisplayed = false;
                        InvalidateRect(hwnd, NULL, TRUE);
                        break;
                    case IDNO:
                        PostQuitMessage(0);
                        break;
                    }
                }
            }
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            char buffer[50];
            sprintf(buffer, "Number of clicks: %d", clickCount);
            HFONT hFont = CreateFont(60, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
            HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
            TextOut(hdc, 0, 0, buffer, strlen(buffer));
            TextOut(hdc, 0, 100, "Target: 100", 11);
            SelectObject(hdc, hOldFont);
            DeleteObject(hFont);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
    int msgboxID = MessageBox(
        NULL,
        (LPCSTR)"Would you like to start the Quantum Radeon Energy Extractor?",
        (LPCSTR)"Start Menu",
        MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2
    );
    switch (msgboxID) {
    case IDYES:
        break;
    case IDNO:
        return 0;
    }
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;
    if(!RegisterClassW(&wc))
        return -1;
    CreateWindowW(L"myWindowClass", L"Quantum Radeon Energy Extractor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 300, NULL, NULL, NULL, NULL);
    MSG msg = {0};
    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}