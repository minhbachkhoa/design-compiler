#include "LinkList.h"


void Init(LIST *A)
{
    A->pHead = NULL;
    A->pTail = NULL;
}

NODE *GetNode(char *arr)
{
    NODE *p = (NODE *)calloc(1, sizeof(struct node)); // cấp phát 1 vùng nhớ có kích thước là struct node ,trả về địa chỉ của vùng nhớ vừa được cấp phát

    if (p == NULL)
    {
        printf("cap phat khong thanh cong\n");
        return p;
    }

    strcpy(p->arr, arr);
    p->pNext = NULL;
    return p;
}

void AddTail(LIST *A, NODE *p)
{
    if (A->pHead == NULL)
    {
        A->pTail = A->pHead = p; // khởi tạo vùng nhớ cho pHead và pTail,tránh lỗi segmentatin fault khi làm việc với con trỏ NULL
        return;
    }
    A->pTail->pNext = p;
    A->pTail = p;
}

// hàm xử lí lệnh "N" , "OLD" , "EU" ,.........
void xulilenhloai_A(char *arr, LIST *l)
{
    NODE *p = GetNode(strtok(arr, "\n"));
    AddTail(l, p);
}
// hàm xử lí lệnh loại "LD I0.0\n" , "ON Q0.0\n",........
void xulilenhloai_B(char *arr, LIST *l)
{
    NODE *p = GetNode(strtok(arr, " "));
    AddTail(l, p);

    char *result = (char *)calloc(15, sizeof(char));

    if (strstr(arr, "LDN") != NULL || strstr(arr, "ON") != NULL || strstr(arr, "AN") != NULL)
    {
        strcpy(result, delete_space(strtok(NULL, "\0"), result));
        p = GetNode(result);
        AddTail(l, p);
        return;
    }

    strcpy(result, delete_space(strtok(NULL, "\n"), result));
    p = GetNode(result);
    AddTail(l, p);
}
// hàm xử lí lệnh loại "S   Q0.3, 1" , "TON   T12, 10"
void xulilenhloai_C(char *arr, LIST *l)
{
    NODE *p = GetNode(strtok(arr, " "));
    AddTail(l, p);

    char *result = (char *)calloc(15, sizeof(char));

    strcpy(result, delete_space(strtok(NULL, ","), result));
    p = GetNode(result);
    AddTail(l, p);

    // p = GetNode(",");
    // AddTail(l,p);

    int i = 0;
    while (result[i] != '\0')
    {
        result[i] = 0;
        i++;
    }

    strcpy(result, delete_space(strtok(NULL, ","), result));
    p = GetNode(result);
    AddTail(l, p);
}
// hàm thêm node ")" vào sau node q
int Sodaungoacphai(LIST *l)
{
    int sodaungoacphai = 0;
    for (NODE *p = l->pHead; p != NULL; p = p->pNext)
    {
        if (strcmp(p->arr, ")") == 0)
        {
            sodaungoacphai++;
        }
    }
    return sodaungoacphai;
}
// hàm thêm dấu " ( "
int Sodaungoactrai(LIST *l)
{
    int sodaungoactrai = 0;
    for (NODE *p = l->pHead; p != NULL; p = p->pNext)
    {
        if (strcmp(p->arr, "(") == 0)
        {
            sodaungoactrai++;
        }
    }
    return sodaungoactrai;
}

//hàm them node p vào đầu danh sách liên kết 
void AddHead(LIST *A,NODE *p){
    if(A->pHead == NULL){
        A->pHead = A->pTail = NULL;
    }
    p->pNext = A->pHead;
    A->pHead = p;
}
// hàm thêm node p vào đầu
void themnodevaodau(LIST *l, NODE *p)
{
    // danh sách rỗng
    if (l->pHead == NULL)
    {
        l->pHead = l->pTail = NULL;
    }
    p->pNext = l->pHead;
    l->pHead = p;
}
// them node x vào sau node p

// hàm thêm node x vào trước node p
void themvaotruoc(LIST *l, NODE *x, NODE *p)
{
    if (p->arr == l->pHead->arr)
    {
        themnodevaodau(l, x);
        return;
    }
    NODE *q;

    for (NODE *k = l->pHead; k != NULL; k = k->pNext)
    {
        // tìm node trước node p => ta gọi node đó là node g
        if (k->arr == p->arr)
        {
            x->pNext = p;
            q->pNext = x; // hàm này sẽ lỗi nếu p là node đầu của danh sách liên kết . lỗi q dang được sử dụng nhưng chưa được khởi tạo vì vậy
                          // ta thêm trường hợp đó lên đầu
        }
        q = k; // khởi tạo q
    }
}

// hàm trả về vị trí của node trong list khi lùi b node

NODE *travevitrinode(LIST *l, int b, int poslist)
{
    NODE *a = (NODE *)malloc(sizeof(struct node));
    NODE *p = l->pHead;

    for (int i = 0; i < poslist - b; i++)
    {
        if (i == poslist - b - 1)
        {
            a = p;
            break;
        }
        p = p->pNext;
    }
    return a;
}
// hàm thêm node ")" vào trước node p

// hàm thêm node "("
void Themngoactrai(LIST *l, NODE *p, NODE *g, int count)
{
    NODE *a = GetNode("(");
    a->pNext = p;
    g->pNext = a;
}

// hàm xuất dữ liệu từ fileSTL
void XuatdulieuSTL(FILE *fileSTL, LIST *l)
{
    char str[50];

    while (fgets(str, 50, (FILE *)fileSTL))
    {
        // Tách chuỗi con lần đầu tiên
        char *arr = (char *)calloc(15, sizeof(char));
        strcpy(arr, str);

        if (strstr(arr, "LDN") != NULL || strstr(arr, "ON") != NULL && strstr(arr, ",") == NULL || strstr(arr, "AN") != NULL)
        {
            arr[strlen(arr) - 1] = 'H';
        }
        if (strstr(arr, ",") != NULL && strstr(arr, " ") != NULL)
        {
            // gọi hàm xử lí chuỗi loại C
            xulilenhloai_C(arr, l);
        }
        else if (strstr(arr, " ") != NULL && strstr(arr, ",") == NULL)
        {
            // gọi hàm xử lí chuỗi loại B
            xulilenhloai_B(arr, l);
        }
        else
        {
            // gọi hàm xử lí chuỗi loại A
            xulilenhloai_A(arr, l);
        }
    }
}

// hàm chuyển dấu "." thành dấu "_"
void Biendoidau(LIST *l)
{
    for (NODE *k = l->pHead; k != NULL; k = k->pNext)
    {
        int i = 0;
        while ((k->arr[i]) != '\0')
        {
            if (k->arr[i] == '.')
            {
                k->arr[i] = '_';
            }
            i++;
        }
    }
}

// hàm nhập dữ liệu cho chuỗi
void nhapdulieuchochuoi(FILE *fileSTL, LIST *l)
{
    fileSTL = fopen("STL.txt", "r");
    if (fileSTL == NULL)
    {
        printf("file mo khong thanh cong");
        return;
    }

    Init(l);
    XuatdulieuSTL(fileSTL, l);
    Biendoidau(l);
}
// hàm xuất dữ liệu danh sách liên kết
/*void Output(FILE *listcode, LIST *l)
{
    for (NODE *p = l->pHead; p != NULL; p = p->pNext)
    {
        fprintf(listcode, "%s", p->arr);
        if (p->pNext == NULL)
        {
            break;
        }
        fputc(',', listcode);
    }
}*/
// hàm xử lí bước 2 tách nhánh
void tachnhanh(LIST *l, FILE *listcode, FILE *listxl)
{
    NODE *p = l->pHead;

    int sodaungoactrailistxl = 0;
    int sodaungoacphailistxl = 0;
    int count = 0;

    //fprintf(listxl, "%s", "listcode = [");
    while (p != NULL)
    {
        if (p->pNext == NULL)
        {
            fprintf(listxl, "%s\0", p->arr);

            break;
        }
        count++;

        if (strcmp(p->arr, "ALD") == 0 || strcmp(p->arr, "OLD") == 0 || strcmp(p->arr, "CTU") == 0 || strcmp(p->arr, "TON") == 0)
        {
            if (sodaungoactrailistxl > sodaungoacphailistxl)
            {
                fprintf(listxl, "%c", ')');
                fprintf(listxl, "%c", ',');
                sodaungoacphailistxl++;
                fprintf(listxl, "%s", p->arr);
                fprintf(listxl, "%c", ',');
            }
            else
            {
                fprintf(listxl, "%s", p->arr);
                fprintf(listxl, "%c", ',');
            }
        }
        else if (strcmp(p->arr, "=") == 0)
        {
            if (sodaungoactrailistxl > sodaungoacphailistxl)
            {
                fprintf(listxl, "%c", ')');
                fprintf(listxl, "%c", ',');
                sodaungoacphailistxl++;
                fprintf(listxl, "%s", p->arr);
                fprintf(listxl, "%c", ',');
            }
            else
            {
                fprintf(listxl, "%s", p->arr);
                fprintf(listxl, "%c", ',');
            }
        }
        else if (strcmp(p->arr, "LD") == 0 || strcmp(p->arr, "LDN") == 0)
        {
            NODE *g = travevitrinode(l, 1, count);
            NODE *k = travevitrinode(l, 3, count);

            if (p == l->pHead || strcmp(k->arr, "=") == 0 || strcmp(g->arr, "N") == 0 || strcmp(g->arr, "ALD") == 0 || strcmp(g->arr, "OLD") == 0)
            {
                fprintf(listxl, "%c", '(');
                fprintf(listxl, "%c", ',');
                sodaungoactrailistxl++;
                fprintf(listxl, "%s", p->arr);
                fprintf(listxl, "%c", ',');
            }
            else
            {
                if (sodaungoacphailistxl == sodaungoactrailistxl)
                {
                    fprintf(listxl, "%c", '(');
                    fprintf(listxl, "%c", ',');
                    sodaungoactrailistxl++;
                    fprintf(listxl, "%s", p->arr);
                    fprintf(listxl, "%c", ',');
                }
                else
                {
                    fprintf(listxl, "%c", ')');
                    fprintf(listxl, "%c", ',');
                    sodaungoacphailistxl++;
                    fprintf(listxl, "%c", '(');
                    fprintf(listxl, "%c", ',');
                    sodaungoactrailistxl++;
                    fprintf(listxl, "%s", p->arr);
                    fprintf(listxl, "%c", ',');
                }
            }
        }
        else
        {
            fprintf(listxl, "%s", p->arr);
            fprintf(listxl, "%c", ',');
        }
        p = p->pNext;
    }
   //fprintf(listxl, "%c", ']');
}
// hàm đọc số kí tự của file
int numChar(FILE *list)
{
    int numstr = 0;
    char c;
    while ((c = fgetc(list)) != EOF)
    {
        numstr++;
    }

    return numstr++;
}

// hàm đẩy dữ liệu vào danh sách liên kết mới
void xuatchofilelistxl(LIST *xl, FILE *listxl)
{
    int numstr = numChar(listxl);
    fclose(listxl);
    listxl = fopen("listxl.txt", "r");
    
    //char str[numstr + 1];
    char *str = (char*)malloc(sizeof(char)*(numstr));

    while (fgets(str, numstr, listxl) != NULL)
    {
        char *p = strtok(str, ",");
        NODE *ptr = GetNode(p);
        AddTail(xl, ptr);

        while (p != NULL)
        {
            p = strtok(NULL, ",");
            // ptr = GetNode(p);
            // AddTail(xl,ptr);
            if (p != NULL)
            {
                ptr = GetNode(p);
                AddTail(xl, ptr);
            }
            else
            {
                break;
            }
        }
    }
}
// hàm thay thế )( thành )((
void replaceOUT(char OUT[], int *n)
{
    for (int i = 0; i < 20; i++)
    {
        if (OUT[i] == ')' && OUT[i + 1] == '(')
        {
            for (int j = 21; j > i + 2; j--)
            {
                OUT[j] = OUT[j - 1];
            }
            OUT[i + 2] = '(';
        }
        break;
    }
    (*n)++;
}
// hàm chèn )((  cho )(
/*
Chèn chuỗi trong C

Tham số
    str1:      Chuỗi ban đầu (không chấp nhận Null)
    str1_size: Độ dài chuỗi str1
    pos:       Vị trí chèn (tính từ đầu chuỗi str1)
    str2:      Chuỗi chèn vào (không chấp nhận Null pointer)
Giá trị trả về
    str1
*/
char *str_insert(char *str1, int str1_size, int pos, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    int len1 = strlen(str1); // hàm strlen tính độ dài chuỗi không bao gồm '\0'.
    int len2 = strlen(str2);

    // Kiểm tra str1 có đủ độ dài để chèn str2 không
    assert(len1 + len2 < str1_size);

    // Kiểm tra vị trí chèn có nằm trong chuỗi str1 không
    assert(len1 >= pos);

    // Làm trống một phạm vi dài với len2 ký tự, từ  str1[pos])
    // Dịch chuyển chuỗi ban đầu về sau, bao gồm cả ký tự `\0'
    memmove(&str1[pos + len2], &str1[pos], len1 - pos + 1);

    // Copy str2 và dán vào khoảng trống mới tạo
    memcpy(&str1[pos], str2, len2);

    return str1;
}
 

//hàm thêm node x vào sau node p
void themvaosau(LIST *A, NODE *x, NODE *p)
{
    for (NODE *k = A->pHead; k != NULL; k = k->pNext)
    {
        if (k->arr == p->arr)
        {
            // tao node mới thêm vào
            NODE *g = p->pNext; // tìm node sau node p
            x->pNext = g;       // trỏ node x vào node g
            p->pNext = x;       //
        }
    }
}
//hàm thay thế ")(" trong OUT bằng ")+("
void thaytheOLD(LIST *OUT){
    NODE *p = OUT->pHead;

    while(p != NULL){
        if(strcmp(p->arr,")") == 0 && strcmp(p->pNext->arr,"(") == 0){
            NODE *ptr = GetNode("+");
            themvaosau(OUT,ptr,p);//thêm node ptr vào sau node p
            break;
        }
        p = p->pNext;
    }
}

//hàm thay thế ")(" trong OUT bằng ")*("
void thaytheALD(LIST *OUT){
    NODE *p = OUT->pHead;

    while(p != NULL){
        if(strcmp(p->arr,")") == 0 && strcmp(p->pNext->arr,"(") == 0){
            NODE *ptr = GetNode("*");
            themvaosau(OUT,ptr,p);
            break;
        }
        p = p->pNext;
    }
}
//hàm thay thế )( trong OUT thành )((
void thaythe(LIST *OUT){
    NODE *p = OUT->pHead;

    while(p!= NULL){
        if(strcmp(p->arr,")") == 0 && strcmp(p->pNext->arr,"(") == 0){
            NODE *ptr = GetNode("(");
            themvaosau(OUT,ptr,p->pNext);
            break;
        }
        p = p->pNext;
    }
}

//hàm check ")(" có trong LIST OUT không?
bool kiemtrachuoi(char *str,LIST *OUT){
    NODE *p = OUT->pHead;

    while(p != NULL){
        if(strcmp(p->arr,")") == 0 && strcmp(p->pNext->arr,"(") == 0){
            return true;
        }
        p = p->pNext;
    }
    return false;
}
//hàm trả về node khi tiến b node
NODE *travenodekhitien(LIST *a,int b,int poslist){
    NODE *n = (NODE *)malloc(sizeof(struct node));
    NODE *p = a->pHead;
    if(poslist + b == 0){
        n = p;
        return n;
    }
    for(int i = 0;i < poslist + b + 1;i++){
        p = p->pNext;
        n = p;
    }
    return n;
}

//hàm tính số network có trong LIST *xl
int numberNetWork(LIST *xl){
    NODE *p = xl->pHead;
    int count = 0;
    while(p != NULL){
        if(strcmp(p->arr,"N") == 0){
            count++;
        }
        p = p->pNext;
    }
    return count;
}
//hàm thuật toán đưa ra biểu thức ngõ ra
void xulytungnetwork(LIST *OUT,LIST *xl,int count){
    NODE *p = travenodekhitien(xl,count,0);
    while(strcmp(p->arr,"N") != 0){
        count++; // đếm số node có trong list 
        if(strcmp(p->arr,"(") == 0 || strcmp(p->arr,")") == 0)
        {
            NODE *ptr = GetNode(p);
            AddTail(OUT,ptr);
        }
        else if(strcmp(p->arr,"LD") == 0 || strcmp(p->arr,"LDN") == 0)
        {
            NODE *ptr = GetNode(p->pNext);
            AddTail(OUT,ptr);
        }
        else if(strcmp(p->arr,"A") == 0 || strcmp(p->arr,"AN") == 0)
        {
            if(kiemtrachuoi(")(",OUT) == true){
                thaythe(OUT);
                NODE *ptr = GetNode("*");
                AddTail(OUT,ptr);
                AddTail(OUT,p->pNext);
                ptr = GetNode(")");
                AddTail(OUT,ptr);
            } 
            else{
                NODE *ptr = GetNode("(");
                AddHead(OUT,ptr);
                ptr = GetNode("*");
                AddTail(OUT,ptr);
                AddTail(OUT,p->pNext);
                ptr = GetNode(")");
                AddTail(OUT,ptr);
            }
        }
        else if(strcmp(p->arr,"O") == 0 || strcmp(p->arr,"ON") == 0){
            if(kiemtrachuoi(")(",OUT)){
                thaythe(OUT);
                AddTail(OUT,p->pNext);
                NODE *ptr = GetNode(")");
                AddTail(OUT,ptr);
            }
            else{
                NODE *ptr = GetNode("(");
                AddHead(OUT,ptr);
                AddTail(OUT,p->pNext);
                ptr = GetNode(")");
                AddTail(OUT,ptr);
            }
        }
        else if(strcmp(p->arr,"ALD") == 0){
            thaytheALD(OUT);
        }
        else if(strcmp(p->arr,"OLD") == 0){
            thaytheOLD(OUT);
        }
        else if(strcmp(p->arr,"=") == 0){
            AddHead(OUT,p);
            AddHead(OUT,p->pNext);
        }
        p = p->pNext;
    }
    count++;
}

//hàm tính số node có trong LIST *xl
int numberNode(LIST *xl){
    int count = 0;
    NODE *p = xl->pHead;
    while(p != NULL){
        count++;
        p = p->pNext;
    }
    return count;
}

//hàm xuất ra biểu thức ngõ ra OUT 
void xuatbieuthucngora(LIST *OUT,FILE *main){
    if(main == NULL){
        printf("file mo khong thanh cong");
    }

    NODE *ptr = OUT->pHead;
    while(ptr !=NULL){
        fprintf(main,"%s",ptr->arr);
        ptr = ptr->pNext;
    }
    fprintf(main,"%s",";\n\0");
    fclose(main);
}
//hàm xóa OUT về trạng thái ban đầu 
void xoalist(LIST *A){
   Init(A);
}
//hàm xử lí biểu thức ngõ ra cho từng network
void xulybieuthucngora(LIST *xl,LIST *OUT){
    int count = 0;

    FILE *main = fopen("main.txt","w");

    if(main == NULL){
        printf("file mo khong thanh cong");
    }
    for(int i = 0;i < numberNetWork(xl); i++){
        for(int j = 0;j < numberNode(xl); j++){
            if(j >= count){
                //xulytungnetwork(OUT,xl,&count);
                xoalist(OUT);
                NODE *p = travenodekhitien(xl,count,0);
                while(strcmp(p->arr,"N") != 0){
                count++; // đếm số node có trong list 
                if(strcmp(p->arr,"(") == 0 || strcmp(p->arr,")") == 0)
                {
                    NODE *ptr = GetNode(p);
                    AddTail(OUT,ptr);
                }
                else if(strcmp(p->arr,"LD") == 0 || strcmp(p->arr,"LDN") == 0)
                {
                    char *arr = p->pNext->arr;
                    NODE *ptr = GetNode(arr);
                    AddTail(OUT,ptr);
                }
                else if(strcmp(p->arr,"A") == 0 || strcmp(p->arr,"AN") == 0)
                {
                    if(kiemtrachuoi(")(",OUT) == true){
                        thaythe(OUT);
                        NODE *ptr = GetNode("*");
                        AddTail(OUT,ptr);
                        char *arr = p->pNext->arr;
                        ptr = GetNode(arr);
                        AddTail(OUT,ptr);
                        ptr = GetNode(")");
                        AddTail(OUT,ptr);
                    } 
                    else{
                        NODE *ptr = GetNode("(");
                        AddHead(OUT,ptr);
                        ptr = GetNode("*");
                        AddTail(OUT,ptr);
                        char *arr = p->pNext->arr;
                        ptr = GetNode(arr);
                        AddTail(OUT,ptr);
                        ptr = GetNode(")");
                        AddTail(OUT,ptr);
                    }
                }
                else if(strcmp(p->arr,"O") == 0 || strcmp(p->arr,"ON") == 0){
                    if(kiemtrachuoi(")(",OUT)){
                        thaythe(OUT);
                        NODE *ptr = GetNode("+");
                        AddTail(OUT,ptr);
                        char *arr = p->pNext->arr;
                        ptr = GetNode(arr);
                        AddTail(OUT,ptr);
                        ptr = GetNode(")");
                        AddTail(OUT,ptr);
                    }
                    else{
                        NODE *ptr = GetNode("(");
                        AddHead(OUT,ptr);
                        char *arr = p->pNext->arr;
                        ptr = GetNode(arr);
                        AddTail(OUT,ptr);
                        ptr = GetNode(")");
                        AddTail(OUT,ptr);
                    }
                }
                else if(strcmp(p->arr,"ALD") == 0){
                    thaytheALD(OUT);
                }
                else if(strcmp(p->arr,"OLD") == 0){
                    thaytheOLD(OUT);
                }
                else if(strcmp(p->arr,"=") == 0){
                    NODE *ptr = GetNode(p->arr);
                    AddHead(OUT,ptr);
                    char *arr = p->pNext->arr;
                    ptr = GetNode(arr);
                    AddHead(OUT,ptr);
                }
                p = p->pNext;
                }
            }
            j = count;
            xuatbieuthucngora(OUT,main);
            break;
        }
    }
}


