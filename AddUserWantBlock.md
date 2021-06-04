# AddUserWantBlock function Explanation.

## Update 

+ ### Fix screen flickering (by using Double Buffering) -Important!!
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

    ```c
    void showBlock() {
	    gotoxy(0, 2);
	    int block_x = 0;
	    int number_x = 0;

	    for (int Block = 0; Block < 7; Block++) {
		    gotoxy(block_x, 2);
		    for (int i = 0; i < 4; i++) {
			    for (int j = 0; j < 4; j++) {
				    if (block[Block][0][i][j] == 1) {
					    gotoxy(block_x + j * 2, 2 + i);
					    print("■");
				    }
			    }
		    }
		    block_x += 8;
	    }

	    for (int number = 0; number < 7; number++) {
		    gotoxy(number_x + 4, 6);
		    char num[2] = { "1" };
		    sprintf_s(num, "%d", number + 1);
		    print(num);
		    number_x += 8;
	    }
    }
    ```
    - SetBlock(int number) is function that set block user wants.

    ```c
    void SetBlock(int number) {
	    blockForm = number - 49;
	    startDropT = clock();
	    enableUserAdd = false;
    }
    ```
+ ### Color 

    - I add Color.

    ```c

        void Color(int color){
            SetConsoleTextAttribute(g_hScreen[g_nScreenIndex],color);
        }

    ```
