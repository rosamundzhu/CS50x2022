<style>
pre {
  overflow-y: auto;
  max-height: 300px;
}
</style>

## Week 1
- The `make hello` command created the hello file containing machine code. （每次更新后需要mark hello,才能再执行新的文件  
- hello is in green with an asterisk, `*`, to indicate that it’s executable, or that we can run it.  
- hello.c is only readable or 可预览的，而非可执行的。  
- `=` assingment operator  
- **error**: hello.c:5:5 indicates that the error was found on line 5, character 5. It looks like string isn’t defined.
```c
#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    //这个是笔记
    string answer = get_string("What's your name? ");
    printf("hello, %s\n", answer);
}
```
- **Header files**, like stdio.h, tells our compiler which libraries to load into our program.
- `counter ++` 或 `counter += 1` 修改时就不用再定义变量的类型
- `constant int MINE = 2` 一般常数的变量要大写，constant后就不能再修改
```c
int main(void)
{
    // Prompt user to agree
    char c = get_char("Do you agree? ");

    // Check whether agreed
    if (c == 'Y' || c == 'y') // c== 要写两遍
    //||是或的意思，&&是and的意思
    //char用的是单引号，string用双引号
    {
        printf("Agreed.\n");
    }
    else if (c == 'N' || c == 'n')
    {
        printf("Not agreed.\n");
    }
}
```
```c
#include <stdio.h>

int main(void)
{
    for (int i = 0; i < 3; i++) 
    //第三个是what you will do after each loop
    {
        printf("meow\n");
    }
}
```
- C中在调用函数之前需要declare your function  
```c
#include <stdio.h>

void meow(int n); //这里先定义函数，写的是int n

int main(void)
{
    meow(3);  //这里给n赋值为3
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
```
```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Width: ");
    }
    while (n < 1); //这个放在下面，先进行do，如果满足while条件，再回到do

    for (int i = 0; i < n; i++)
    {
        printf("?");
    }
    printf("\n");
}
```
```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1);

    // For each row
    for (int i = 0; i < n; i++)
    {
        // For each column
        for (int j = 0; j < n; j++)
        {
            // Print a brick
            printf("#");
        }

        // Move to next row
        printf("\n");
    }   
}
```
- unsigned intergal 是不包含负数的，因此可以显示2^32-1个数字。
- char一般占用1 byte of memory (8 bits)
- float(real numbers): take up four bytes of memory(32 bits)
- double: more precise than float, 8 bytes of memory(64 bits)  
- bool和string需要 `#inclue <cs50.h> `
```int x = (expr)?5:6``` 如果满足条件就是5否则是6
```c
int x = GetInt()
switch(x)
{
    case 5:
        printf("Five, ");
    case 4:
        printf("Four, ");
    case 1:
        printf("Four, ");
    default:
        print("blast-off\n")
}
```
- control + c 停止循环
- control + l 清空上面的记录
- mv greedy.c greddy.c 重新命名greedy.c 变成greddy.c  
- while是不知道什么时候停止；do-while也是，但是至少会运行一次；for是运行a specific times
- `cp -r pset0 pset3` 把pset0中的文件也一起都复制了

***

## Week 2
- `clang hello.c` 可以直接使hello.c可compile 
- `clang -o hello hello.c -lcs50` clang to use `hello` as the output filename, and use `hello.c` as the source code；如果使用了其他library，需要在后面加上`-lcs50` (`make`可以自动生成)

Compiling source code into machine code is actually made up of four smaller steps:
1. preprocessing;
2. compiling; (converts into assembly language)
3. assembling; (translate it to binary)
4. linking; 

最后抽象/简化为了`make`.  
**Array**
```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int scores[3]; //用[3]来表示how many values we want to store

    scores[0] = get_int("Score: "); //index是从0开始的
    scores[1] = get_int("Score: ");
    scores[2] = get_int("Score: ");

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
    //因为scores是int，所以需要除以3.0才能变成浮点数
}
```
```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_int("How many scores? ");

    int scores[n]; //几个数字取决于输入几

    for (int i = 0; i < 3; i++) //通过for loop使code更整洁
    {
      scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
}
```
**strings**
- 如果strings会end with a special character, `'\0'`,说明需要四个字符来存储三个character
- 用下面这个程序来确定字符的长度
```c
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Name: ");

    int i = 0;
    while (name[i] != '\0')
    {
        i++;
    }
    printf("%i\n", i);
}
```
- 可以用C’s string library 中的`strlen`来看字符串长度
```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>
  
int main(void)
{
    string name = get_string("Name: ");
    int length = strlen(name);
    printf("%i\n", length);
}
```
```c 
//转换成大写
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", s[i] - 32); //大小写之间的距离是32
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
```
```c
//用ctype中的islower
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++) //写在第一个‘;’前只需要判断一次长度；
    {
        if (islower(s[i])) //是否是小写，t/f
        {
            printf("%c", s[i] - 32);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}
```
- 或者利用函数`toupper`直接转换成大写，不再判断
```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        printf("%c", toupper(s[i]));
    }
    printf("\n");
}
```
**Command-line arguments**  
`argc` and `argv` are two variables that our main function will now get automatically when our program is run from the command line.   
`argc` is the argument count, or number of arguments (words) typed in.  
`argv[]`, argument vector (or argument list), is an array of the arguments (words) themselves, and there’s no size specified since we don’t know how big that will be ahead of time.  
argv里面存储的都是string，不可以直接对数字进行计算
```c
#include <cs50.h>
#include <stdio.h>
  
int main(int argc, string argv[])
{
    printf("hello, %s\n", argv[0]); //输出的是程序名
}
```
```
$ make argv
$ ./argv David
hello, ./argv
```
```c
#include <cs50.h>
#include <stdio.h>
  
int main(int argc, string argv[])
{
    if (argc == 2) 
    {
        printf("hello, %s\n", argv[1]); //如果长度是2，就输出后面的字符
    }
    //如果没有这个else，输入./argv会输出hello, (null)
    else //少于2或者超过2都是输出world；
    {
        printf("hello, world\n");
    }
}
```
```
$ make argv
$ ./argv
hello, world
$ ./argv David
hello, David
$ ./argv David Malan
hello, world
```
```c
#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    printf("hello, %s\n", argv[1]);
    return 0; //一般不需要加这个，因为By default, our main function returns 0 to indicate nothing went wrong
}
```
- `bool truthtable[] = {false, true, true};` 可以这样赋值,不用明确是几
- `bool battleship[10][10]` 10*10 grid of cells
- Array不能直接复制，必须assign element by element
- most variables in C are passed by value, but arrays are passed by reference
-----
## Week 3  
Big *O* notation: decribe running time  
Big *O*, on the order of, is the upper bound of number of steps, or how many steps it might take, in the worst case.

Big $\Omega$, big Omega notation, describes the lower bound of number of steps for our algorithm

Big $\Theta$, big Theta, describe running times of algorithms if the upper bound and lower bound is the same.

`strcmp`, string compare, which compares strings for us.  `strcmp` returns a negative value if the first string comes before the second string, 0 if the strings are the same, and a positive value if the first string comes after the second string.  
`if (strcmp(names[i], "Ron") == 0)`, so we can check whether our two strings are actually equal.
`if (strcmp(names[i], "Ron"))`, then any non-zero value, positive or negative, would be considered true, which would be the opposite of what we want.  
**data structure**
```c
typedef struct //tells the compiler that we are defining our own data structure
{
    string name;
    string number;
}
person; //the name of the data structure
```
```c
#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Carter";
    people[0].number = "+1-617-495-1000";

    people[1].name = "David";
    people[1].number = "+1-949-468-2750";

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "David") == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
```
linear search: ***O***(n), $\Omega$(1)  
binary search:先排序， ***O***(log n), $\Omega$(1)  
selection sort: 每次找到最小的，然后放到最前面max: n+(n-1)+(n-2)+...+1。 ***O***($n^2$), $\Omega$($n^2$)  
bubble sort:1和2对比，2和3对比... 循环n-1词，每次n-1次对比。 ***O***($n^2$), $\Omega$($n$)  
merge sort: 不断拆分成两半后先对最小单元进行sort，然后对两个单元进行merge。 ***O***($n$ $log$ $n$), $\Omega$($n$ $log$ $n$).  

计时的code：`time ./[sort_file] [text_file.txt].`   
e.g. `time ./sort1 reversed10000.txt.`

very helpful to solve pset in WEEK 3 in CS50: 
> https://gist.github.com/ndiecodes/c6b18883870681fa84c17126ead8ed05

--------  
## Week4  
**hexadecimal**: 
> 0 1 2 3 4 5 6 7 8 9 A B C D E F  

With two digits, we can have a maximum value of FF, or $16^1*15+16^0*15=255$.  
Two digits in hexadecimal can conveniently represent the value of a byte in binary.  
十六进制数以数字0和字母x的组合0x或0X开头.

**address and pointer**  
A **pointer** is a variable that stores an address in memory, where some other variable might be stored.  
A pointer is nothing more than an adress. 

A pointer is a data item whose
- *value* is a memory address
- *type* describes the data located at that memory address  

`int *p = &n;`  
- The `&` operator can be used to get the address of some variable, as with `&n`.   
- And the `*` operator declares a variable as a pointer, as with `int *p`, indicating that we have a variable called `p` that *points* to an `int`.  
- `int *p = &n;` to store the address of a variable `n` into a pointer `p` , *表明存储的不仅是int，而是代表的是address  

如果要创建multiple pointers on the same line, ` int *pa, *pb, *pc;`


**segmentation faults**: tried to read or write to memory we don’t have permission to.  
The `*` operator is also the **dereference operator**, which goes to an address to get the value stored there. 
```c
#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", p); //这里是输出address
    printf("%p\n", &n); //和上面code的作用一样
    printf("%i\n", *p); //这里是输出value，*的作用是go to that address
}
```
```
$ ./address
0x7ffda0a4767c
50
```
We declared `p` to be an `int *`, `*p` is an `int`.  
we have one variable, `p`, with the value of some address, like `0x123` stored.  
address一般都是8 bytes, or 64 bits  
类似于一个arrow, 主要是指向某一个变量

**string**  
`string s = "HI!"` is the same as `char *s = "HI!";` 
pointer指向的是string的第一个字符s[0]
```c
#include <stdio.h>

int main(void)
{
    char *s = "HI!"; //s是后面字符串的地址
    printf("%p\n", s); //输出地址
    printf("%p\n", &s[0]); //和上面的地址一样
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);
}
```
```
$ make address
$ ./address
0x402004
0x402004
0x402005
0x402006
0x402007
```
`typedef <old name> <new name>;`  
`typedef char *string` 定义string为char *
```c
struct car
{
    ...
};
car_t

car_t mycar;
```

go to addresses directly:
```c
#include <stdio.h>

int main(void)
{
    char *s = "HI!"; 
    printf("%c\n", *s); //
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
}
```
`char *s = "HI!"; `创建两个对象：  
- 包含值`'H'`, `'I'`,`'!'`, `'\0'`的4个char的只读数组，该数组没有名称，并且具有静态存储持续时间 （这意味着在程序的整个生命周期中都活着）； 和  
- 一个指针类型为s的变量，称为s ，它使用该未命名只读数组中第一个字符的位置进行初始化。

输出的是该地址下的char  
`*s` goes to the address stored in s  
`*(s + 1)` goes to the location in memory with the next character, an address that is one byte higher.
```c
//Array也同样适用
#include <stdio.h>

int main(void)
{
    int numbers[] = {4, 6, 8, 2, 7, 5, 0};
    // 不需要写*
    // an array can actually be treated as the address of the first element in that array.

    printf("%i\n", *numbers);
    printf("%i\n", *(numbers + 1)); //不需要考虑how big the type of data it is
    printf("%i\n", *(numbers + 2));
    printf("%i\n", *(numbers + 3));
    printf("%i\n", *(numbers + 4));
    printf("%i\n", *(numbers + 5));
    printf("%i\n", *(numbers + 6));
}
```
对于string类型，如果直接对比`if (s == t)`,会显示different. 因为Each “string” is a pointer, `char *`, to a different location in memory.  
可以用`if (strcmp(s, t) == 0)`进行对比 (0 is for the same)

如果是copy a string
```c 
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("s: ");

    string t = s; //copy是指向同一个地址的

    t[0] = toupper(t[0]);

    printf("s: %s\n", s);
    printf("t: %s\n", t);
}
```
```
$ make copy
$ ./copy
s: hi!
s: Hi!
t: Hi!
```
可以发现`s`和`t`都大写了。因为set `s` and `t` to the same value, or the same address, they’re both pointing to the same character, 因此capitalized the same character in memory。  

**Memory allocation**  
dynamic memory allocation  
```c
int x = GetInt();
float stack_array[x];
float *heap_array = malloc(x * sizeof(float));
free(heap_array); //avoid memory leaking
```

```c
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");

    char *t = malloc(strlen(s) + 1);

    if (t == NULL)
    {
        return 1;
    }
    //check whether computer is out of memory

    strcpy(t, s); //copying the characters
    //a library function, strcpy
    // right to the left
    // t = s still not works

    if (strlen[t] > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t); 
    //remember to call free on t, since we allocated it ourselves.
}
```
```
$ make copy
$ ./copy
s: hi!
s: hi!
t: Hi!
```
- The argument to `malloc` is the number of bytes we’d like to use.  
- the length of `s` and need to add 1 for the terminating null character.  
- If our computer is out of memory, `malloc` will return `NULL`, the null pointer, or a special value of all `0` bits that indicates there isn’t an address to point to.  

`int *x = malloc(3 * sizeof(int));` use `sizeof` to get enough memory for 3 times the size of an int  生成int的size三倍的memory

`valgrind` is a command-line tool that we can use to run our program and see if it has any memory-related issues.  

例如, 运行`valgrind ./memory`。  
- 可能会写`Invalid write of size 4 at ... memory.c:9, `，表明了第九行command出现了size 4 (buffer overflow)
- `12 bytes ... are definitely lost`, in that we’ve allocated them, but not freed them.

**swap**  
注意在调用swap function时，变量调换只在swap内部有效，是 local variables。
```c
void swap(int a, int b)
{
    printf("a is %i, b is %i\n", a, b);
    int tmp = a;
    a = b;
    b = tmp;
    printf("a is %i, b is %i\n", a, b);
}
```
如果没有给`y`指定memory，`*y =13`会报错，成为**garbage values**
```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 42;
    // *y =13 
    printf("x:%i\n", *x);

    y = x; //指向同一个address

    *y = 13;
    printf("x:%i\n", *x);
    printf("y:%i\n", *y);

    free(x); //free 1个就行了
}
```
```
x:42
x:13
y:13
```
**Memory layout**  
- The **machine code** section is our compiled program’s binary code. When we run our program, that code is loaded into memory.  
- Just below, or in the next part of memory, are **global variables** we declared in our program.  
- The **heap** section is an empty area from where malloc can get free memory for our program to use. As we call malloc, we start allocating memory from the top down.  
- The **stack** section is used by functions and local variables in our program as they are called, and grows upwards.
- there maybe **heap overflow**, or **stack overflow**.

By passing in the address of `x` and `y`, our swap function will be able to change the original values:
```c
#include <stdio.h>

void swap(int *a, int *b); //这里记得也要变

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);
    printf("%p, %p\n", &x, &y);
    swap(&x, &y); //这里pass in的是地址
    printf("x is %i, y is %i\n", x, y);
    printf("%p, %p\n", &x, &y);
}

void swap(int *a, int *b) 
{
    //把传入进来的地址利用*转移成数字
    int tmp = *a; //把a地址下转译的数字传入到tmp
    *a = *b; //把b地址转译的数字赋值给a地址上的数值
    *b = tmp; //把tmp上的数值赋予b地址上的数值
    printf("%p, %p\n", a, b);
}
```
```
x is 1, y is 2
0x7ffef08b5dcc, 0x7ffef08b5dc8
0x7ffef08b5dcc, 0x7ffef08b5dc8
x is 2, y is 1
0x7ffef08b5dcc, 0x7ffef08b5dc8
```
The addresses of `x` and `y` are passed in from main to swap with `&x` and `&y`, and we use the `int *a` syntax to declare that our swap function takes in pointers.
交换的时候地址始终没有变，变的是每个地址上存储的值。
<br/>
<br/>

**scanf**  
scanf("输入控制符", 输入参数);  
功能：将从键盘输入的字符转化为“输入控制符”所规定格式的数据，然后存入以输入参数的值为地址的变量中
```c
#include <stdio.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x); //将输入的值转换为int格式，并存储在&x的位置上
    printf("x: %i\n", x);
}
```
`&i`又称为“取地址i”，就相当于将数据存入以变量`i`的地址为地址的变量中。

如果是字符串类型，需要先allocate memory
```c
#include <stdio.h>

int main(void)
{
    char *s = malloc(4); //allocate memory for s
    //string只能输入长度为3的，最后留一个给`\0`
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
    free(s);
}
```
<br/>

**Files**  
` FILE *ptr = fopen(<filename>, <operation>); `
ptr: a generic name for file pointer
`"r"` is read the file; `"w"` is write (override); `"a"` is append.  
`fclose(<file pointer>)` close the file  

`char ch = fgetc(<file pointer>)`  
`fget()` reads and returns the next character form the file pointed to. (operation should be "r")  

`$ cat` prints the content  
```c
char ch;
while((ch = fgetc(ptr)) != EOF) //EOF is the end of file
    printf("%c", ch);
```

`fputc(<character>, <file pointer>);` writes or appends the specfic character (e.g. `fputc('!', ptr1)`)

<br/>

`fread(<buffer>, <size>, <qty>, <file pointer>)` (operation should be "r")  
`<buffer>` is a pointer to the location and memory wehre we want to store the inforamation
```c
int arr[10]; //store them in arr, actually pointers
fread(arr, sizeof(int), 10, ptr) 
```
```c
double *arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);
```
```c
char c; //this is not a pointer, it is just a variable
fread(&c, sizeof(char), 1, ptr);  
//so we use &c to indicate that that's the address where we want to store this one byte of information
```
<br/>


`fwrite(<buffer>, <size>, <qty>, <file pointer>)` 
from the buffer to the file
```c
int arr[10]
fwrite(arr, sizeof(int), 10, ptr);
```
```c
char c; 
fwrite(&c, sizeof(char), 1, ptr); 
```
<br/> <br/> 
Examples：
```
// Saves names and numbers to a CSV file
  
#include <cs50.h>
#include <stdio.h>
#include <string.h>
  
int main(void)
{
    // Open CSV file
    FILE *file = fopen("phonebook.csv", "a");
    if (!file)
    {
        return 1;
    }
  
    // Get name and number
    string name = get_string("Name: ");
    string number = get_string("Number: ");
  
    // Print to file
    // `fprintf` to write to a file.
    fprintf(file, "%s,%s\n", name, number);
  
    // Close file
    fclose(file);
}
```

 
```c
// Detects if a file is a JPEG
  
#include <stdint.h>
#include <stdio.h>

//define a BYTE as 8 bits
typedef uint8_t BYTE;
  
int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        return 1;
    }
  
    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }
  
    // Read first three bytes
    // use `fread` to read from a file
    BYTE bytes[3];
    fread(bytes, sizeof(BYTE), 3, file);
  
    // Check first three bytes
    // compare the first three bytes (in hexadecimal) to the three bytes required to begin a JPEG file.
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff)
    {
        printf("Yes, possibly\n");
    }
    else
    {
        printf("No\n");
    }
  
    // Close file
    fclose(file);
}
```
```c
// Only shows the color red
#include "helpers.h"
  
// Only let red through
void filter(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = 0x00;
            image[i][j].rgbtGreen = 0x00;
        }
    }
}
```
</br>
every file on the computer lives on the disk drive, either in **hard disk drive (HDD)** or a **solid-state drive** (but just storage space)  
manipulation and use of datat only take place in RAM.</br></br>

**call stack**  
**stack frames**, **function frames**  
more than one function's stack frame may exist in memory at a given time.  
- if main() calls move(), move() then calls direction(), all three functions have open frames.  
- These frames are arranged in a stack.  
- Most-recently called function is always on the top of the stack.  
- If call a new function, that function immediately gets space and memory, and is **put** on top of the call stack. And it becomes the active frame.  
- When a function finishes its work, such as by returning, most commonly, or perhaps reaching the end of the line if it's a void function, it doesn't have a return value, that frame is what's called **popped off** of the stack.</br></br>

**LAB**

WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample.  
After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.

`uint8_t` is a type that stores an 8-bit unsigned (i.e., not negative) integer. We can treat each byte of a WAV file’s header as a `uint8_t` value.  
`int16_t` is a type that stores a 16-bit signed (i.e., positive or negative) integer. We can treat each sample of audio in a WAV file as an `int16_t` value.  

--------  
## Week5  
how to add a new value:

第一种方法 recap:  
array
```c
//Recap
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int *list = malloc(3 * sizeof(int));
    // 如果直接写int list[3] 就没有办法修改大小了

    if (!list)
    {
        return -1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // resize the old array to be of size 4
    // 用realloc指定下old array，无需再做copy的工作
    // 会自动释放old block
    int *tmp = realloc(list, 4 * sizeof(int));

    if (!tmp)
    {
        // but HERE list still points to valid memory, so clean up first:
        free(list); 
        //a safety check, free the orginal list
        return -1;
    }

    tmp[3] = 4; 

    // remember new array
    list = tmp;
    //所以不需要在free(tmp), free(list)相当于free(tmp)

    // print new array
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // free new array
    free(list);
    return 0; //最后记得加上这个
}
```

Then `realloc` replaces the old array for you already it works like this:

```c
void* realloc(void* oldData, size_t desired)
{
    // retain currently allocated memory size from pointer
    // that's OS/compiler specific knowledge, usually stored somewhere
    // in front of the memory the pointer points to, but not (legally)
    // accessible by you...
    size_t old = ...;

    if(desired <= old)
    {
        return oldData;
    }
    void* newData = malloc(desired);
    if(newData)
    {
        memcpy(newData, oldData, oldSize);
        free(oldData); // !!!
    }
    return newData;
}
```

另一种方式是使用 **linked list**  
With a linked list, we can store a list of values in different parts of memory.  
可以存储在任何memory that are free.
此时values不一定相互连接了，而是每个数值使用两个space用来储存value和一个pointer指向下一个value的address.  
这样就节约了copy的时间，但是need more space for both the value and the address of the next value.  
这种一种time和space的tradeoff.  
Doubly-Linked Lists  
the group of boxes with a value and pointer is a **node**   

**singly-linked lists**

```c
typedef struct node //暂时命名一个叫struct node的
{
    int number; //a number
    struct node *next;  //and a pointer (8 bytes)
    //compile是从上到下阅读的，需要先写上node，否则会出错
}
node; //这里把名字缩减为node
```
```c
//这个的作用和上面是一样的，但是这个名字叫做struct node
//typedef的作用就是将这个重新命名为node
struct node 
{
    int number; //a number
    struct node *next;
}
```
```c
//第二种方法
//to remember an empty list
node *list = NULL; 

//To add a node, first need to allocate some memory
node *n = malloc(sizeof(node));

if (n != NULL) //if (able to get memory back from malloc)
{
    //set a value
    n->number = 1; 
    //set the pointer to the next node to null
    n->next = NULL; 
}

list = n;
```
```c
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void){
    node *list = NULL; 
    node *n = malloc(sizeof(node));
    if (n == NULL){
        return 1;
    }
    n->number = 1;
    n->next = NULL;
    
    //update list to point to new node
    list = n;

    //add a number to list
    n = malloc(sizeof(node));
    if (n == NULL){
        free(list);
        return 1;
    }
    n->number = 2;
    n->next = NULL;
    list->next = n;

    n = malloc(sizeof(node));
    if (n == NULL){
        free(list->next);
        free(list);
        return 1;
    }
    n->number = 3;
    n->next = NULL;
    list->next->next = n;


    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("%i\n", tmp->number);
    }
    //需要free的是adress，而不是field或是什么

    //free list
    //With a linked list, we’re responsible for freeing the memory for each node separately, since we allocated it separately as well.
    while (list != NULL)
    {
        //using another tmp pointer to remember the next node before we free the current node
        node *tmp = list->next; //temp中储存的是地址
        free(list);
        list = tmp;
    }
    return 0;
}
```
worse scenario:  
linked notes需要从头开始search, need to follow each node, 因此take $O(n)$ for search  
insert also takes $O(n)$, since we might need to insert our node at the end. 但是如果不在意顺序，就是$O(n)$  
best scenario:
$\Omega(1)$ to search or insert

如果使用了binary search tree, 时间会缩短为$O(log n)$


```c
//implements a list of numbers as a binary search tree

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
}
node;

void free_tree(node *root);
void print_tree(node *root);


int main(void){
    //tree of size 0
    node *tree = NULL; 

    //add number to list
    node *n = malloc(sizeof(node));
    if (n == NULL){
        return 1;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    
    //update list to point to new node
    tree = n;

    //add a number to list
    n = malloc(sizeof(node));
    if (n == NULL){
        free(tree);
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;
    tree->left = n; //initialize the tree's child to be n

    n = malloc(sizeof(node));
    if (n == NULL){
        free(tree->left);
        free(tree);
        return 1;
    }
    n->number = 3;
    n->right = NULL;
    tree->right = n;

    print_tree(tree);
    free_tree(tree);
}

void free_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left); 
    free_tree(root->right);
    free(root); //注意最后才能free root
    //just free the address in that variable
}

void print_tree(node *root)
{
    if (root == NULL)
    {
        return;
    }
    //print from min to max
    print_tree(root->left); //recursion
    printf("%i\n", root->number);
    print_tree(root->right);
}
```
```c
bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number); //数据类型只需要定义一次
    }
    else if (number > tree->number)
    {
        return search(tree->right, number); 
    }
    else //number == tree->number
    {
        return true;
    }
}
```
**doubly-linked lists**  
每个data包含三个指标 下一个node还会指回上一个node

**hash table**  
hash function and array   
the worst case running time for searching a hash table is $O(n)$.  
*linear probing*  
*clustering*  向下找空白的，排在下面  
*chaining* 是先用arrays的hash code分层，每层是linked lists，假设有100个hash code，这样运行速度就变成了$O(n)/100$.  

**trie**  
每个child都是一个array  
不管有多少名字存储，检索一个名字最多的步骤就等于longest name的长度，namely $O(1)$ (constant time)  
lookup is fast; delection is easy;  
already sorted  
但是会占用大量的memory，且很多memory都会是null

**queues**  FIFO  
**stack** LIFO


