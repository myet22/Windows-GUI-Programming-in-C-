#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 2
#define SAVE_FILE_BUTTON 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenu(HWND);
void AddControls(HWND);

HWND hType, hId, hName, hAddress, hPhone, hSpec, hOut, hEdit;


class Fac_info {

public:

    char type[30];
    char id[10];
    char name[30];
    char address[150];
    char phone[25];
    char spec[30];
    char out[300];

};


    void write_file(char* path){

        FILE *file;
        file = fopen(path, "w");

        int _size = GetWindowTextLength(hOut);
        char *data = new char[_size+1];
        GetWindowText(hOut, data, _size+1);

        fwrite(data, _size+1, 1, file);

        fclose(file);

    }

    void save_file(HWND hWnd){

        OPENFILENAME ofn;

        char file_name[100];

        ZeroMemory(&ofn, sizeof(OPENFILENAME));

        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = hWnd;
        ofn.lpstrFile = file_name;
        ofn.lpstrFile[0] = '\0';
        ofn.nMaxFile = 300;
        ofn.lpstrFilter = "ALL files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
        ofn.nFilterIndex = 1;

        //Need to add a reference to libcomdlg32.a
        GetSaveFileName(&ofn);

        write_file(ofn.lpstrFile);

    }

    void OutputText(char *Out, char *Type, char *Id, char *Name, char *Address, char *Phone, char *Spec){

        strcat(Out, "Health Care Facility Type : ");
        strcat(Out, Type);
        strcat(Out, "\r\n\r\nFacilities List :");
        strcat(Out, "\r\n\tFacilities Id :");
        strcat(Out, Id);
        strcat(Out, "\r\n\tFacilities Name :");
        strcat(Out, Name);
        strcat(Out, "\r\n\tAddress :");
        strcat(Out, Address);
        strcat(Out, "\r\n\tPhone Number :");
        strcat(Out, Phone);
        strcat(Out, "\r\n\tSpecialty :");
        strcat(Out, Spec);

    }

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

    //建立主視窗
    CreateWindowW(L"WindowClass", L"Stephanie Wang's assignment", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 650, NULL, NULL, NULL, NULL);

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

            case SAVE_FILE_BUTTON:

                //show the type info
                Fac_info fi;
           //     char type[30], id[10], name[30], address[150], phone[25], spec[30], out[300];
                GetWindowText(hType, fi.type, 30);
                GetWindowText(hId, fi.id, 10);
                GetWindowText(hName, fi.name, 30);
                GetWindowText(hAddress, fi.address, 150);
                GetWindowText(hPhone, fi.phone, 25);
                GetWindowText(hSpec, fi.spec, 30);

                OutputText(fi.out, fi.type, fi.id, fi.name, fi.address, fi.phone, fi.spec);

                SetWindowText(hOut, fi.out);
                save_file(hWnd);

                break;
        }

        break;

    case WM_CREATE:
        AddControls(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);

    }
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

    CreateWindowW(L"Button", L"SAVE", WS_VISIBLE | WS_CHILD, 190, 325, 100, 25, hWnd, (HMENU)SAVE_FILE_BUTTON, NULL, NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE, 50, 375, 380, 200, hWnd, NULL, NULL, NULL);

}

