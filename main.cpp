#include <windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 2
#define FUN_BUTTON 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenu(HWND);
void AddControls(HWND);

HWND hType, hId, hName, hAddress, hPhone, hSpec, hOut;
HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

    WNDCLASSW wc = {0};

    //視窗屬性
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //視窗背景顏色
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); //鼠標形狀
    wc.hInstance = hInst;
    wc.lpszClassName = L"WindowClass"; //視窗class name
    wc.lpfnWndProc = WindowProcedure; //視窗訊息處理指標

    if(!RegisterClassW(&wc))
        return -1;

    //建立新視窗
    CreateWindowW(L"WindowClass", L"Stephanie Wang's assignment", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 880, NULL, NULL, NULL, NULL);

    //迴圈取得視窗訊息
    MSG msg = {0};
    while( GetMessage(&msg, NULL, NULL, NULL) ){
        TranslateMessage(&msg); //傳出
        DispatchMessage(&msg); //解碼
    }

    return 0;
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){

    //視窗訊息切換
    switch(msg){

    case WM_COMMAND:

        switch(wp){

            case FILE_MENU_EXIT:
                DestroyWindow(hWnd);
                break;

            case FILE_MENU_NEW:
                MessageBeep(MB_ICONINFORMATION);
                break;

            case FUN_BUTTON:

                char type[30], id[10], name[30], address[150], phone[25], spec[30], out[300];
                GetWindowText(hType, type, 30);
                GetWindowText(hId, id, 10);
                GetWindowText(hName, name, 30);
                GetWindowText(hAddress, address, 150);
                GetWindowText(hPhone, phone, 25);
                GetWindowText(hSpec, spec, 30);

                //字串複製cpy串接cat
                strcat(out, "Health Care Facility Type : ");
                strcpy(out, type);
                strcat(out, "Facilities List :\n");
                strcat(out, "Facilities List :");

                SetWindowText(hOut, out);

                break;

        }

        break;

    case WM_CREATE:
        AddMenu(hWnd);
        AddControls(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
}


void AddMenu(HWND hWnd){

    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();

    //subMenu
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "EXIT");

    //rootMenu
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    SetMenu(hWnd, hMenu);

}


void AddControls(HWND hWnd){

    CreateWindowW(L"Static", L"Health Care Facility Type :", WS_VISIBLE | WS_CHILD, 50, 50, 200, 50, hWnd, NULL, NULL, NULL);
    hType = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 230, 50, 190, 23, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Static", L"Facilities List :", WS_VISIBLE | WS_CHILD, 50, 100, 200, 50, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Facility ID :", WS_VISIBLE | WS_CHILD | SS_RIGHT, 80, 135, 100, 50, hWnd, NULL, NULL, NULL);
    hId = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 135, 220, 23, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Facility Name :", WS_VISIBLE | WS_CHILD | SS_RIGHT, 80, 170, 100, 50, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 170, 220, 23, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Address :", WS_VISIBLE | WS_CHILD | SS_RIGHT, 80, 205, 100, 50, hWnd, NULL, NULL, NULL);
    hAddress = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 205, 220, 23, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Phone Number :", WS_VISIBLE | WS_CHILD | SS_RIGHT, 60, 240, 120, 50, hWnd, NULL, NULL, NULL);
    hPhone = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 240, 220, 23, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Specialties :", WS_VISIBLE | WS_CHILD | SS_RIGHT, 80, 275, 100, 50, hWnd, NULL, NULL, NULL);
    hSpec = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 200, 275, 220, 23, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Save as .Txt", WS_VISIBLE | WS_CHILD, 190, 325, 100, 25, hWnd, (HMENU)FUN_BUTTON, NULL, NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 375, 380, 400, hWnd, NULL, NULL, NULL);

}

