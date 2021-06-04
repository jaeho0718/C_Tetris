# AddUserWantBlock function Explanation.

## Update 

+ ### Fix screen flickering (by using Double Buffering)
    - To show content, You should replace 'printf' to 'print'. (If you use printf function,Nothing appears.)
    ``` c
    void print(const char* string){
        DWORD dw;
        WriteFile(g_hScreen[g_nScrenIndex],string,strlen(string),&dw,NULL);
    }
    /*
        g_hScreen[g_nScrenIndex] is current buffer.
        If you want to write format character, look at the following example.
    */
    int num = 0;
    char a[2] = {"C"};
    //To use format character, Use 'sprintf_s' function.
    sprintf_s(a,"%d",num); 
    print(a);
    ```

    - system("cls") replace to ScreenClear() (please remove all system("cls"). It is appropriate to call ScreenClear() only once )

    - ScreenFlipping() serves to change the buffer.

+ ### Add function that user can select the block when user delete 3lines.
    - Use enableUserAdd value to check user deletes 3lines. 
    ``` c
    //In main() Function.
    while (true){
        ScreenClear(); //remove all content
        DrawMap();
        if (!enableUserAdd){
            //If User deletes 3lines, Change screen to show the block that user can choose.
        }
        InputKey();
        ScreenFlipping();
    }

    //In InputKey() Function.
    if (enableUserAdd){
        //check what block the user has selected
    }else{
        //check Rotation.
    }

    //In BlockToGround() Funtion.
    if (!enableUserAdd){
        //only call RandomForm() when enableUserAdd value is false.
    }
    ```

    - showBlock() is function that show the block user can choose.

    - SetBlock(int number) is function that set block user wants.

+ ### Color 

    - I add Color.

    ```c

        void Color(int color){
            SetConsoleTextAttribute(g_hScreen[g_nScreenIndex],color);
        }

    ```
