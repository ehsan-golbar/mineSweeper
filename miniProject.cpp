#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>

void row_column (int& , int& , int ) ;// با گرفتن اندیس خانه ، شماره سطر و ستون آنرا حساب می کند
void show_chart ( char selected[ 5 ][ 5 ] );// برای چاپ کل زمین بازی بعد از هر اقدام بازیکن 
void catch_row_column (int&  , int& );// برای گرفتن مقدار سطر و ستون از بازیکن
void value1 ( int houses[ 25 ], int min_index[ 6 ] ) ;// برای حساب کردن تعداد مین های اطراف هر خانه (برای خانه های ستون های دوم تا چهارم)
void value2 (int houses[ 25 ], int min_index[ 6 ]) ;//(برای خانه های  ستون  پنجم) برای حساب کردن تعداد مین های اطراف هر خانه
 void value3 (int houses[ 25 ], int min_index[ 6 ]); // برای حساب کردن تعداد مین های اطراف هر خانه (برای خانه های ستون اول)
void winORlose (char selected[ 5 ][ 5 ] , bool& , bool& );// چک می کند که ایا توانسته تمام خانه های بدون مین را بگوید یا نه
void index_array_compute ( int , int  , int& ) ;// با گرفتن سطر و ستون ، اندیس خانه را حساب می کند 
void end_show ( int houses[ 25 ], int min_index[ 6 ], char selected[ 5 ][ 5 ]) ;// برای نمایش کل صفحه بازی در اخر بازی
/*
 ___ ___ ___ ___ ___
|_0_|_1_|_2_|_3_|_4_|
|_5_|_6_|_7_|_8_|_9_|
|_10|_11|_12|_13|_14|
|_15|_16|_17|_18|_19|
|_20|_21|_22|_23|_24|
*///  اندیس خانه ها به صورت بالا فرض شده است  

int main ()
{
   srand(time(NULL));
    int  houses[25], min_index[6];
    cout << " Welcome to our game "<<endl;
    cout << " You must open every squere without min "<<endl;
    cout << " You can use question_mark to guess the place of mins "<<endl;
    for ( int i = 0 ; i < 6 ; i++ ){
         min_index[ i ] =  rand () % 25 ; // خانه هایی که قرار است مین در انها به صورت تصادفی باشد 
         for (int j = i - 1 ; j >= 0 ; j-- ){
            if ( min_index[ i ] == min_index[ j ]){//برای جلوگیری از تکراری بودن اعداد شانسی 
                i--;
                  break;
              }
         }
      
    }

         value1 ( houses,  min_index ) ;
         value2 ( houses,  min_index) ;
         value3 ( houses,  min_index) ;
        //سه خط بالا برای حساب کردن تعداد مین ها در اطراف هر خانه است
        int person_want , row , column, index_array = 0 ,  question_mark = 0 ;
        char selected[5][5] = { {95,95,95,95,95}, {95,95,95,95,95}, {95,95,95,95,95}, {95,95,95,95,95}, {95,95,95,95,95}} ;// برای چاپ ( _ ) یا اعداد یا (؟) می باشد 
            bool start = true , win_lose = false ; // برای قطع کردن حلقه به کار می روند  

        do {
               cout << "1) select   2) guess Min  3) exit "<<endl;
            cin >>  person_want ;
            if ( person_want == 1 ){

                    catch_row_column (row , column);
                     index_array_compute (row , column , index_array ) ;
                        // دو خط بالا برای گرفتن سطر و ستون از کاربر و محاسبه اندیس خانه است
                          if ( selected[row-1][column-1] == 63)
                        {
                            cout << "You've already guessed there is a Min here"<<endl;
                            continue;
                        }
                        // شرط بالا در صورتیه که کاربر ، خانه ای که قبلا علامت سوال روی آن گذاشته است رو انتخاب کند 
                         for (int i = 0 ; i < 6 ; i++){
                             if ( index_array == min_index[i])
                            {
                                 start = false ;
                                win_lose = false ;
                             break;
                             }
                         }
                         if (start)
                         {}
                         else 
                         break;
                       // حلقه بالا برای چک می کند که کاربر ، خانه ای که درآن مین است را انتخاب کرده یا نه
                         selected[row-1][column-1] =  houses[ index_array ] + 48;
                               show_chart ( selected) ;
                            // دو خط بالا برای نمایش صفحه بازی ، با نشان دادن انتخاب او
                                winORlose ( selected , start , win_lose);
                                if (start == 0)
                                break;
            }

            else if ( person_want == 2){
            catch_row_column (row , column);
                index_array_compute (row , column , index_array ) ;
                          // دو خط بالا برای گرفتن سطر و ستون از کاربر و محاسبه اندیس خانه است
                        if (selected[row-1][column-1] == 63){
                            selected[row-1][column-1] = 95 ;
                        }
                        else {
                            if ( selected[row-1][column-1] == 95)
                                selected[row-1][column-1] = 63 ;
                            else {
                            cout << "You've already opened this house !!"<<endl ;
                            continue;
                            } 
                        }
                        // شرط های بالا برای این است که روی خانه های انتخاب نشده علامت سوال بگذارد واز گذاشتن علامت سوال روی خانه ای که عددی را نشان میدهد جلوگیری کند
                            for (int i = 0 ; i < 5 ; i++){
                                for (int j = 0 ; j < 5 ; j++){
                                    if ( selected[i][j] == 63)
                                        question_mark++;
                                }
                            }
                            if (question_mark > 6 ){
                                cout << "You can only guess 6 Mins!"<<endl;
                                question_mark = 0;
                                selected[row-1][column-1] = 95 ;
                                continue;
                            }
                            question_mark = 0;
                             // چند خط بالا چک می کند که تعداد علامت سوال ها از 6 تا بیشتر نشود

                            show_chart ( selected) ;// نشان دادن زمین بازی بعد از انتخاب کاربر
            }

            else if (person_want == 3){// درصورت مایل بودن کاربر به خروج از بازی
                break;
            }
            else {// در صورتی که کاربر عددی غیر مجاز را وارد کند 
                cout << "please chose one of the numbers below"<<endl;
                continue ;
            }
        }while (true );

     end_show (  houses,  min_index,  selected) ;
        show_chart ( selected) ;
        //دو خط بالا برای نمایش کل صفحه بازی در صورت بردن ، باختن و یا انصراف از بازی
    if (win_lose)// تعیین برد ، باخت و انصراف 
    cout  << "YOU WON!!";
    else 
    cout  << "Boom!!";
    printf ("%c", 7 );
}

void show_chart ( char selected[ 5 ][ 5 ] )
{
     for ( int j = 0 ; j < 5 ; j++ )
                                 {    
                                    if ( j == 0  ){

                                    for (int k = 1 ; k <= 5 ; k++)
                                          cout << ' ' << "___" ;
                                           cout << endl;
                                          }
      
                                     for (int i = 0 ; i < 5 ; i++)
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

void end_show ( int houses[ 25 ], int min_index[ 6 ], char selected[ 5 ][ 5 ])
{
         int temp , row , column ; 
        for (int i = 0 ; i < 25 ; i++){
              temp = i;
              row = 1 ;
             column = 0 ;
            for ( ;temp >= 5;  ){
               temp -= 5 ;
                row++;
              }

              for ( ; temp >= 0 ;){ 
            temp--;
              column++;
              }
              selected[row-1][column-1] = houses[i] + 48;
  
            }//برای همه خانه های بدون مین ، تعداد مین های مجاور را حساب می کند

        for (int i = 0 ; i < 6 ; i++){
         temp = min_index[i];
              row = 1 ;
             column = 0 ;
            for ( ;temp >= 5;  ){
               temp -= 5 ;
                row++;
              }

              for ( ; temp >= 0 ;){ 
            temp--;
              column++;
              }
              selected[row-1][column-1] = 66;
  
            }// خانه هایی که در ان مین هستند را مشخص می کند
} 


void index_array_compute ( int row , int column , int& index_array)
{
                        index_array = 0 ;
                     for ( int i = 1 ; i < row ; i++ )
                         index_array += 5 ;
                    for (int i = 1 ; i < column ; i++ )
                         index_array += 1;
}

void winORlose (char selected[ 5 ][ 5 ] , bool& start , bool&  win_lose )
{
                 bool end = false ;
             for (int i = 0 ; i < 5 ; i++){
                      for (int j = 0 ; j < 5 ; j++ ){
                            if ( selected[i][j] != 95)
                             {
                                  if ( i == 4 && j == 4 )
                                  {       start = false ;
                                        win_lose = true;
                                             break;
                                 }
                              }
                          else {
                              end = true ;
                                 break;
                              }
                                    }
                                   if (end)
                                   break ; 
                                }
}

 void row_column (int& row , int& column, int index_array)
 {

               int temp;
                     row = 1 ;
                     column = 0; 
                         temp = index_array;
                    for ( ;temp >= 5;  ){
                       temp -= 5 ;
                           row++;
                       }

                     for ( ; temp >= 0 ;){ 
                          temp--;
                          column++;
                      }
  
 }

void catch_row_column (int& row , int& column)
{
        while (true )
               {
                     cout << "row : " ;
                        cin >> row  ;
                     cout <<  "column : ";
                         cin >> column ;
                         if ( row > 5 || row < 1){
                             cout << "the number of row is invalied "<<endl;
                             continue ;
                         }
                            if ( column > 5 || column < 1){
                             cout << "the number of column is invalied "<<endl;
                             continue ;
                         }
                        return ;
                
                }
}


void value2 (int houses[ 25 ], int min_index[ 6 ])
 {
      int i = 4 , value = 0;
       
        do {// تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 
              if ( ( i + 4 ) <= 24 )
             { 
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 4 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

            if ( ( i + 5 ) <= 24 )
            {
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 5 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }
           
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 1 ) == min_index[ j ] ){
                     value++;
                    break;
                }
             }

                if ( ( i - 5 ) >= 0 )
              {  
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 5 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
        }
                if ( ( i - 6 ) >= 0 )
             {   
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 6 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
           }
             houses[i] = value;
             i = i + 5 ;
            value = 0;
        }while ( i <= 24 );//خانه های ردیف اخر 
 }          

 void value1 ( int houses[ 25 ], int min_index[ 6 ] )
 {
       int i =  1 , value = 0 ;

     do {//تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 

           if (i == 4 || i ==5 || i == 9 || i == 10 || i == 14 || i == 15 || i == 19 || i == 20 || i == 24  ){
            i++;
            continue ;
        }

         if ( ( i - 6 ) >= 0 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 6 ) == min_index[ j ] ){
                     value++;
                     
                    break;
                }
            }
         }

          if ( ( i - 5 ) >= 0 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 5 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

          if ( ( i - 4 ) >= 0 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 4 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

          if ( ( i - 1 ) >= 0 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 1 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

          if ( ( i + 6 ) < 25 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 6 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
          }

           if ( ( i + 5 ) < 25 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 5 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

          if ( ( i + 4 ) < 25 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 4 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

          if ( ( i + 1 ) < 25 ){
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 1 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

        houses[i] = value;
        i++;
        value = 0 ;
     }while ( i <= 23 );//محاسبه برای همه خانه ها به جز خانه های ردیف اول و ردیف اخر 
    
      
 }

 void value3 (int houses[ 25 ], int min_index[ 6 ])
 {
     int  i = 0, value = 0 ;

        do {//تعداد مین های موجود در هشت خانهمجاور (درصورت وجود) هر خانه را چک می کند 
              if ( (i + 6) <= 24  )
           {   
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 6 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         }

            if ( ( i + 5 ) <= 24 )
          {  
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 5 ) == min_index[ j ] ){
                     value++;
                    break;
                }
            }
         
        }
           
             for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i + 1 ) == min_index[ j ] ){
                     value++;
                    break;
                }
             }

                    if ( ( i - 4 ) >= 0 )
                {    
                 for ( int j = 0 ; j < 6 ; j++ ){
                if ( ( i - 4 ) == min_index[ j ] ){
                     value++;
                    break;
                      }
                    }
                }


                if ( ( i - 5 ) >= 0 )
                {
                    for ( int j = 0 ; j < 6 ; j++ ){
                 if ( ( i - 5 ) == min_index[ j ] ){
                         value++;
                        break;
                          }
                     }
                 }

             houses[i] = value;
             i = i + 5 ;
            value = 0;
        }while ( i <= 20 );//خانه های ردیف او ل 
 }
