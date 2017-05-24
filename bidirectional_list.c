#include <stdio.h>
#include <stdlib.h>

//リスト用構造体定義
struct LIST{
	struct LIST *next;
	struct LIST  *prev;
	int value;
};

//リストの先頭を定義
struct LIST list;

//関数のプロトタイプ宣言
void Add(int);
void AddNext(int,int);
void Del(int);
void DelHere(int);
void Display();
void Release();

int main(void)
{

	//最初は何もないので自分自身が最後でもある
	list.next=&list;
	//循環リストだと前の要素も自分なので自分のポインタをセット
	list.prev=&list;


	char answer='5';
	int figure;
	int ith;

	puts("What do you do?\n 0. finish, 1.add, 2.delete, 3.list, 4.add-here, 5.delete-here\n");

	while(answer!='0'){

		scanf("%c",&answer);

		//入力バッファに残る\nをクリアする
		fflush(stdin);
		getchar();

		switch(answer){

		case '1':
		  puts("Put number added to list");
		  scanf("%d",&figure);
		  getchar();
		  Add(figure);
		  break;

		case '4':
		  puts("Put number added to list");
		  scanf("%d %d",&ith,&figure);
		  getchar();
		  AddNext(ith, figure);
		  break;


		case '2':
		  puts("Put number deleted in list");
		  scanf("%d",&figure);
		  getchar();
		  Del(figure);
		  break;

		case '5':
		  puts("Put which number deleted in list");
		  scanf("%d",&ith);
		  getchar();
		  DelHere(ith);
		  break;

		case '3':
		  Display();
		  break;
		default:
		  puts("Put number");
		  break;
		}
		//入力バッファに残る\nをクリアする
		fflush(stdin);

		puts("What do you do? \n 0. finish, 1. add, 2. delete, 3. list, 4. add-here, 5. delete-here\n");

	}

	//解放
	Release();

	return 0;

}

void Add(int temp){

	//新規確保用
	struct LIST *p;
	//現在の末尾のリストのポインタ；
	struct LIST *next;
	//末尾直前のポインタ
	struct LIST *prev;

	//新しいリストの領域を確保
	//p=(LIST*)malloc(sizeof(LIST));
	p=(struct LIST*)malloc(sizeof(struct LIST));



	//値を代入
	p->value=temp;
	//次の要素は先頭要素のポインタ
	p->next=&list;

	//最初は先頭が末尾直前のポインタになる
	prev=&list;

	//末尾のポインタまで移動
	for(next=list.next;next!=&list;next=next->next){
			prev=next;
	}

	//リストを連結する。
	prev->next=p;
	//新しく確保した要素のprevメンバにも前の要素のポインタを入れる
	p->prev=prev;

	puts("have added");

}


//Add-Next
void AddNext(int ith, int temp){

	//新規確保用
	struct LIST *p;
	//現在の末尾のリストのポインタ；
	struct LIST *next;
	//末尾直前のポインタ
	struct LIST *prev;

	//新しいリストの領域を確保
	//p=(LIST*)malloc(sizeof(LIST));
	p=(struct LIST*)malloc(sizeof(struct LIST));



	//値を代入
	p->value=temp;
	//次の要素は先頭要素のポインタ
	p->next=&list;

	//最初は先頭が末尾直前のポインタになる
	prev=&list;

	//i番目のポインタまで移動
	int i=0;
	for(next=list.next;next!=&list;next=next->next){
	  i++;
	  if (i == ith) break;
	  prev=next;
	}

	//リストを連結する。
	p->next=prev->next;
	prev->next=p;
	//新しく確保した要素のprevメンバにも前の要素のポインタを入れる
	p->prev=prev;
	next->prev=p;

	puts("have added to Next");

}

void Del(int temp){

	//削除要素の直前の要素のポインタ
	struct LIST* prev;

	//最初は先頭要素の次のリストからチェックしてるので、
	//削除要素の直前の要素は先頭要素になる。
	prev=&list;

	//リストを末尾(先頭要素のポインタ)までループ
	struct LIST *p;
	for(p=list.next;p!=&list;p=p->next){

		//その値があれば
		if(p->value==temp){

			//削除要素の前のリストにつなげる
			//その前に次の要素が末尾ならつなげる必要ないのでチェック
			if(p->next!=&list){

				//削除直前の要素につなげる
				prev->next=p->next;
				//削除した次の要素のprevに、削除直前の要素のポインタをセット
				p->next->prev=prev;

				//削除対象要素の解放
				free(p);

				return;
			}

			//末尾要素に先頭要素のポインタを保存
			prev->next=&list;
			//先頭要素のprevに末尾要素のポインタを第ニュ
			list.prev=prev;

			//削除対象要素の解放
			free(p);

			puts("have deleted");

			return;
		}

		prev=p;

	}
	puts("Cannot find");

}


//Del-Here
void DelHere(int ith){

	//削除要素の直前の要素のポインタ
	struct LIST* prev;

	//最初は先頭要素の次のリストからチェックしているので、
	//削除要素の直前の要素は先頭要素になる。
	prev=&list;

	//リストを末尾(先頭要素のポインタ)までループ
	struct LIST *p;
	int i=0;
	for(p=list.next;p!=&list;p=p->next){

		//その値があれば
	  i++;
	  if(i == ith){ //ip->value==temp){

	    //削除要素の前のリストにつなげる
	    //その前に次の要素が末尾ならつなげる必要ないのでチェック
	    if(p->next!=&list){

	      //削除直前の要素につなげる
	      prev->next=p->next;
	      //削除した次の要素のprevに、削除直前の要素のポインタをセット
	      p->next->prev=prev;

	      //削除対象要素の解放
	      free(p);

	      return;
			}

	    //末尾要素に先頭要素のポインタを保存
	    prev->next=&list;
	    //先頭要素のprevに末尾要素のポインタを第ニュ
	    list.prev=prev;

	    //削除対象要素の解放
	    free(p);

	    puts("have deleted");

	    return;
	  }

	  prev=p;

	}
	puts("Cannot find");

}












void Display(){

	if(list.next==&list){
		puts("Nothing, yet");
		return;
	}

	//NULLになるまで全部表示
	struct LIST *p;
	int i=0;
	for(p=list.next;p!=&list;p=p->next){
	  i++;
	  printf(" (%d) %d,",i,p->value);
	}

	puts("");

}

void Release(){

	//次のリストのポインタ
	struct LIST *next;
	//削除対象のポインタ
	struct LIST *del;

	next=list.next;

	//NULLになるまでループ
	while(next!=&list){
		//削除対象のポインタを保存
		del=next;
		//次のリストのポインタを取得しとく
		next=next->next;

		free(del);
	}
}
