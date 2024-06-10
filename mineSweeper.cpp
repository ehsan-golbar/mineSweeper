#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include "clui.h"
#include <cmath>
enum upDown{
  up,down
};
struct names_scores {
  char name[20];
  float scores;
};
void row_column (int& , int& , int ) ;// با گرفتن اندیس خانه ، شماره سطر و ستون آنرا حساب می کند
void show_chart ( char selected[ 21 ][ 21 ], int  );// برای چاپ کل زمین بازی بعد از هر اقدام بازیکن 
void catch_row_column (int&  , int& );// برای گرفتن مقدار سطر و ستون از بازیکن
void value1 ( int houses[], int min[], int, int ) ;// برای حساب کردن تعداد مین های اطراف هر خانه (برای خانه های ستون های دوم تا چهارم)
void value2 (int houses[], int min[], int, int) ;//(برای خانه های  ستون  پنجم) برای حساب کردن تعداد مین های اطراف هر خانه
 void value3 (int houses[], int min[], int, int); // برای حساب کردن تعداد مین های اطراف هر خانه (برای خانه های ستون اول)
void winORlose (char selected[5][5] , bool& , bool& );// چک می کند که ایا توانسته تمام خانه های بدون مین را بگوید یا نه
void index_array_compute ( int , int  , int&, int ) ;// با گرفتن سطر و ستون ، اندیس خانه را حساب می کند 
void end_show ( int houses[ 25 ], int min[ 6 ], char selected[ 5 ][ 5 ], int, int ) ;// برای نمایش کل صفحه بازی در اخر بازی
void choose ( upDown , int&  );
void assign_mins ( int min[], int , int );
void print_choose ( int );
void move_table (  char selected[21][21], int& , int& , int , int , int min[], int houses[]  );
void new_game ( int& , int&  );
int open ( char selected[21][21] , int , int , int min[], int houses[],int ,int, int );
float score ( char selected[21][21], int , int  );
void show_leader ( names_scores list_score[ 5 ], int  ); 
void exit_leader ();
/*
 ___ ___ ___ ___ ___
|_0_|_1_|_2_|_3_|_4_|
|_5_|_6_|_7_|_8_|_9_|
|_10|_11|_12|_13|_14|
|_15|_16|_17|_18|_19|
|_20|_21|_22|_23|_24|
*///  اندیس خانه ها به صورت بالا فرض شده است  
names_scores list_score[5] = { {"", 0}};
int index_score = 0  ;
int main ()
{
  
    init_clui();
      int last_position = 1, new_position = 1 ;
   upDown which ;
   clear_screen();
  print_choose( new_position );
    char ch;
     while((ch=getch())!=32)
    {
        if (!ch)
        {
            ch=getch();
             clear_screen();
            switch(ch)
            {
                case 77:   print_choose(last_position); break;
               case 75:  print_choose(last_position); break;
                case 72:which = up ;  choose ( which, last_position);break;
                case 80: which = down ;  choose ( which, last_position);break;   
            }
        }
    }
    clear_screen();
    int min_index = 25, house_index= 400 ;
     int  houses[ house_index ], min[ min_index ];
    switch (last_position){
        case 1 : {
          if ( index_score == 5)
              exit(0);
            new_game( min_index, house_index);
            assign_mins( min , min_index, house_index);
             value1 ( houses,  min, min_index, house_index ) ;
         value2 ( houses,  min, min_index, house_index) ;
         value3 ( houses,  min, min_index, house_index) ;
        }break ;
        case 2 : cout << "not developed yet"; delay(3000);exit(0); break; 
        case 3 :  cin >> list_score[index_score].name; main(); break; 
        case 4 :show_leader ( list_score, index_score ); exit_leader(); break ;
        case 5 : exit(0);  break;
    }
        int person_want , row , column, index_array = 0 ,  question_mark = 0, last_column = 0, last_row = 0 ;
        char selected[ 21 ][ 21 ];
        for ( int i = 0 ; i < 21 ; i++ ){        // برای چاپ ( _ ) یا اعداد یا (؟) می باشد 
            for ( int j = 0 ; j < 21 ; j++ )
            selected[ i ][ j ] = 95 ;
        }
        selected[ last_row ][ last_column ]= 63 ;
        show_chart( selected, house_index );
        
        
        move_table( selected, last_row, last_column, house_index,min_index,min,houses );
        
            
}
void show_chart ( char selected[ 21 ][ 21 ], int house_index )
{
     for ( int j = 0 ; j < sqrt( house_index) ; j++ )
                                 {    
                                    if ( j == 0  ){
                                    for (int k = 1 ; k <=  sqrt( house_index) ; k++)
                                          cout << ' ' << "___" ;
                                           cout << endl;
                                          }
                                     for (int i = 0 ; i <  sqrt( house_index) ; i++)
                                     {
                                          cout <<'|'<<'_';
                                        printf( "%c", selected[j][i]); // نمایش عدد یا ( _ ) و یا (؟)
                                        cout << '_'; 
                                     }
                                     cout << '|';
                                 cout << endl;
                            }
                            cout << endl;
}

void end_show ( int houses[  ], int min[  ], char selected[ 21 ][ 21 ], int house_index, int min_index )
{
         int temp , row , column ; 
       /* for (int i = 0 ; i < house_index ; i++){
              temp = i;
              row = 1 ;
             column = 0 ;
            for ( ;temp >= sqrt( house_index );  ){
               temp -= sqrt(house_index) ;
                row++;
              }
              for ( ; temp >= 0 ;){ 
            temp--;
              column++;
              }
              selected[row-1][column-1] = houses[i] + 48;
            }//برای همه خانه های بدون مین ، تعداد مین های مجاور را حساب می کند
        */
        for (int i = 0 ; i < min_index ; i++){
         temp = min[i];
              row = 1 ;
             column = 0 ;
            for ( ;temp >= sqrt(house_index);  ){
               temp -= sqrt(house_index) ;
                row++;
              }
              for ( ; temp >= 0 ;){ 
            temp--;
              column++;
              }
              selected[row-1][column-1] = 66;
            }// خانه هایی که در ان مین هستند را مشخص می کند
} 
void index_array_compute ( int row , int column , int& index_array, int house_index)
{
                        index_array = 0 ;
                     for ( int i = 0 ; i < row ; i++ )
                         index_array += sqrt( house_index ) ;
                    for (int i = 0 ; i < column ; i++ )
                         index_array += 1;
}
void value2 (int houses[], int min[], int min_index, int house_index)
 {
      int i = sqrt( house_index ) - 1  , value = 0;
        do {// تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 
              if ( ( i + sqrt( house_index) - 1 ) < house_index )
             { 
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index) - 1 ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
            if ( ( i + sqrt( house_index ) ) < house_index )
            {
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index )  ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - 1 ) == min[ j ] ){
                     value++;
                    break;
                }
             }
                if ( ( i - sqrt( house_index ) ) >= 0 )
              {  
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - sqrt( house_index )) == min[ j ] ){
                     value++;
                    break;
                }
            }
        }
                if ( ( i - (sqrt( house_index ) + 1 ) ) >= 0 )
             {   
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - (sqrt( house_index ) + 1 ) )== min[ j ] ){
                     value++;
                    break;
                }
            }
           }
             houses[i] = value;
             i = i + sqrt( house_index ) ;
            value = 0;
        }while ( i < house_index  );//خانه های ردیف اخر 
 }          

 void value1 ( int houses[], int min[], int min_index, int house_index )
 {
       int i =  1 , value = 0 ;
     do {//تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 
         bool special_index = false;
   for ( int j = sqrt( house_index ) ; j < house_index ; j += sqrt( house_index )){
      if ( j == i )
      {
        break ;
        special_index = true ;
      }
   }
   if ( special_index )
   continue;
   special_index = false;
    for ( int j = sqrt( house_index ) - 1 ; j < house_index ; j += sqrt( house_index )){
      if ( j == i )
      {
        break ;
        special_index = true ;
      }
   }
   if ( special_index )
   continue;
         if ( ( i -( sqrt( house_index ) + 1) ) >= 0 ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if (  ( i -( sqrt( house_index ) + 1) ) == min[ j ] ){
                     value++;
                     
                    break;
                }
            }
         }
          if ( ( i - sqrt( house_index ) ) >= 0 ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - sqrt( house_index ) ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
          if ( ( i - (sqrt( house_index ) - 1) ) >= 0 ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if (  ( i - (sqrt( house_index ) - 1) ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
          if ( ( i - 1 ) >= 0 ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - 1 ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
          if ( ( i + sqrt( house_index ) + 1 ) < house_index ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index ) + 1  ) == min[ j ] ){
                     value++;
                    break;
                }
            }
          }
           if ( ( i + sqrt( house_index ) ) < house_index ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index ) ) == min[ j ] ){
                     value++;
                    break;
                }
            }
           }
          if ( ( i + sqrt( house_index ) - 1  ) < house_index ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index ) - 1 ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
          if ( ( i + 1 ) < house_index ){
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + 1 ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
        houses[i] = value;
        i++;
        value = 0 ;
     }while ( i < house_index );//محاسبه برای همه خانه ها به جز خانه های ردیف اول و ردیف اخر 
 }

 void value3 (int houses[], int min[], int min_index, int house_index  )
 {
     int  i = 0, value = 0 ;
        do {//تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 
              if ( (i + sqrt( house_index ) + 1 ) < house_index  )
           {   
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( (i + sqrt( house_index ) + 1 ) == min[ j ] ){
                     value++;
                    break;
                }
            }
         }
            if ( ( i + sqrt( house_index ) ) < house_index )
          {  
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + sqrt( house_index ) ) == min[ j ] ){
                     value++;
                    break;
                }
            }
        }
             for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i + 1 ) == min[ j ] ){
                     value++;
                    break;
                }
             }
                    if ( ( i - (sqrt( house_index ) - 1 ) ) >= 0 )
                {    
                 for ( int j = 0 ; j < min_index ; j++ ){
                if ( ( i - (sqrt( house_index ) - 1 ) ) == min[ j ] ){
                     value++;
                    break;
                      }
                    }
                }
                if ( ( i - sqrt( house_index ) ) >= 0 )
                {
                    for ( int j = 0 ; j < min_index ; j++ ){
                 if ( ( i - sqrt( house_index ) ) == min[ j ] ){
                         value++;
                        break;
                          }
                     }
                 }
             houses[i] = value;
             i = i + sqrt( house_index ) ;
            value = 0;
        }while ( i <= house_index - sqrt( house_index) );//خانه های ردیف او ل 
 }
 void choose ( upDown which, int& last_position )
{
  int new_position ;
    if ( which == up ){
      if ( last_position - 1 >= 1 )
      new_position =  --last_position;
      else 
      new_position = 5;
      print_choose( new_position );
    }
    if ( which == down ){
      if ( last_position+1 <= 5)
      new_position =  ++last_position;
      else 
      new_position = 1 ;
      print_choose( new_position );
    }
    last_position = new_position ;
}

void print_choose ( int new_position )
{
    int a = 1, b= 2, c = 3, d = 4, e = 5 ;
    cout << "New Game";
    if ( a == new_position )
    cout << "  " << "<--" ;
    cout << endl<< "Load Game" ; 
    if ( b == new_position )
    cout << "  " << "<--" ;
    cout << endl<< "Change Name";
    if ( c == new_position )
    cout << "  " << "<--" ;
    cout << endl<< "Leaderboard";
    if ( d == new_position )
    cout << "  " << "<--";
    cout << endl<< "Quit";
    if ( e == new_position )
    cout << "  " << "<--" ;
    cout << endl;
}

void new_game ( int& min_index, int& house_index )
{
    int choosen_number;
    cout << "1) easy    number of mins = 4 , table = 5 * 5 "<< endl ;
    cout << "2) medium    number of mins = 28 , table = 12 * 12 "<< endl ;
    cout << "3) hard    number of mins = 96 , table = 20 * 20 "<< endl ;
    cout << "4) costum size  "<<endl;
     choosen_number = getch() ;
    switch( choosen_number )
    {
      case '1': clear_screen(); min_index = 4 ; house_index = 25 ; break;
      case '2':  clear_screen(); min_index = 28 ; house_index = 144 ; break;
      case '3':  clear_screen(); min_index = 96 ; house_index = 400 ; break;
      case '4': {
        clear_screen();
        do {
           cout << " 4 < mins < 21    mins = ";
        cin >> min_index;
         if ( min_index < 5 || min_index >20 )
        {
          cout << " the number of mins is invalied ";
          delay(2000);
          clear_screen();
          continue ;
          }
          else 
          break ;
        }while ( true );
         do {
           cout << "24 < table < 401    table ( like : 5 * 5 = 25, your choice must be square ) = ";
        cin >> house_index;
         if ( house_index < 25 || house_index >400 )
        {
          cout << "the number of table is invalied ";
          delay(2000);
          clear_screen();
          continue;
        }
          else 
          clear_screen();
          break ;
        }while ( true );
      }break;
      default:  clear_screen(); new_game( min_index, house_index ); break; 
    }
}



void assign_mins ( int min[],int min_index, int house_index )
{
     srand(time(NULL));
     for ( int i = 0 ; i < min_index ; i++ ){
         min[ i ] =  rand () % house_index ; // خانه هایی که قرار است مین در انها به صورت تصادفی باشد 
         for (int j = i - 1 ; j >= 0 ; j-- ){
            if ( min[ i ] == min[ j ]){//برای جلوگیری از تکراری بودن اعداد شانسی 
                i--;
                  break;
              }
         }
      
    }
}

void move_table ( char selected[21][21], int& last_row, int& last_column, int house_index, int min_index, int min[], int houses[])
{
    char ch;
    int  last_ascii = 95, index_array;
    while((ch=getch())!=27)
    {   
        if (!ch)
        {
            ch=getch();
            switch(ch)
            {
                case 77:
                selected[ last_row ][ last_column ] = last_ascii ;
                    if ( last_column + 1 <= sqrt( house_index ) - 1 )
                   {
                     last_ascii = selected[ last_row ][ last_column+1 ];
                      selected[ last_row ][ last_column + 1 ] = 63 ;
                    last_column = last_column + 1 ;
                    }
                    else {
                      last_column = 0 ;
                      last_ascii = selected[ last_row ][ last_column ] ;
                      selected[ last_row ][ last_column ] = 63;
                    }
                    clear_screen();
                    show_chart( selected , house_index );
                   // Right
                    break;
                case 75:
                  selected[ last_row ][ last_column ] = last_ascii ;
                  if ( last_column - 1 >= 0 )
                  {
                  last_ascii = selected[ last_row ][ last_column-1 ];
                  selected[ last_row ][ last_column - 1 ] = 63 ;
                  last_column = last_column - 1 ;
                  }
                  else {
                    last_column = sqrt( house_index ) - 1 ;
                    last_ascii = selected[ last_row ][ last_column ];
                    selected[ last_row ][ last_column ] = 63 ;
                  }
                  clear_screen();
                  show_chart( selected , house_index );
                   //Left
                    break;
                case 72:
                 selected[ last_row ][ last_column ] = last_ascii ;
                if ( last_row - 1 >= 0 )
                {
                  last_ascii = selected[ last_row-1 ][ last_column ];
                  selected[ last_row - 1 ][ last_column ] = 63;
                last_row = last_row -1 ;
                }
                else {
                  last_row = sqrt( house_index ) - 1 ;
                  last_ascii =selected[ last_row ][ last_column ];
                  selected[ last_row ][ last_column ] = 63;
                }
                clear_screen();
                show_chart( selected , house_index );
                   // Up
                    break;
                case 80:
                 selected[ last_row ][ last_column ] = last_ascii ;
              if ( last_row + 1 <= sqrt( house_index ) - 1 ){
                  last_ascii = selected[ last_row+1 ][ last_column ];
                selected[ last_row + 1 ][ last_column ] = 63 ;
                last_row = last_row + 1 ;
              }
              else {
                last_row = 0 ;
                last_ascii =selected[ last_row ][ last_column ];
                selected[ last_row ][ last_column ] = 63;
              }
              clear_screen();
              show_chart( selected , house_index );
                  // Down
                    break;
                    case 27 : exit(0); break ;
            }
        }
        switch( ch )
        {
        case 32 : {
            clear_screen();
            if ( last_ascii == 70 )
            {
              show_chart(selected, house_index);
            }
            else {
           last_ascii = open(selected,last_row,last_column,min,houses,min_index,house_index, last_ascii);
            show_chart(selected, house_index);
            }
            }break;
            case 102 : {
                clear_screen();
                if ( last_ascii == 70)
                {
                  selected[ last_row ][ last_column ] = 95;
                  last_ascii = 95 ;
                  show_chart( selected , house_index );
                }
                else if ( last_ascii != 95)
                {
                    show_chart( selected , house_index );
                }
                else
                {
                  selected[ last_row ][ last_column ] = 70 ;
                last_ascii = 70;
                show_chart( selected , house_index );
                }
            }break ; 
        }
    }
  main();
}

int open ( char selected[21][21] , int last_row, int last_column, int min[], int houses[],int min_index,int house_index, int last_ascii)
{
  int index_array = 1;
  if ( last_ascii == 70 )
    return last_ascii ;
    index_array_compute( last_row, last_column, index_array, house_index);
    for (int i = 0 ; i < min_index ; i++){
            if ( index_array == min[i]){
              cout << "BOOM !!"<<   endl;
               list_score[index_score].scores = score ( selected, house_index, min_index);
               index_score++;
              end_show( houses,  min,  selected, house_index , min_index );
              show_chart( selected , house_index );
              exit_leader();      
            }
      }
    selected[last_row][last_column] =  houses[ index_array ] + 48;
    for ( int i = 0 ; i < min_index ; i++ ){
      if ( index_array == min[ i ]){
        selected[last_row][last_column] = 66 ;
        break;
      }
    }
    int show = selected[last_row][last_column];
   // cout << show << endl;
   // delay(3000);
    return selected[last_row][last_column];
}

float score ( char selected[21][21], int house_index, int min_index )
{
  float point = 0 ;
  float house_index_float, min_index_float;
  house_index_float = house_index;
  min_index_float = min_index ;
   for ( int i = 0 ; i < sqrt(house_index) ; i++){
      for ( int j = 0 ; j < sqrt(house_index) ; j++){
        if ( selected[i][j] != 95 && selected[i][j] != 70 && selected[i][j] != 63 )
          point++;
      }
   }
   float result =  (point / (house_index - min_index)) * 100.0 ;
   return result ;
}

void show_leader ( names_scores list_score[5], int index_score )
{
   for ( int i = 0, j = 1  ; i < index_score ; i++, j++){
    cout << j << " ) " << list_score[i].name << "       "  ;
    printf("%.2f",list_score[i].scores );
    cout <<endl;
   }
}


void exit_leader ()
{
      char ch;
      cout <<" to return to menu click on <Esc> ";
    while((ch=getch())!=27)
    {
        if (!ch)
        {
            ch=getch();
            switch(ch)
            {
                default :; 
            }
        }
    }
    main();
}