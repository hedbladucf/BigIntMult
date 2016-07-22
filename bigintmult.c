/*
OSCAR HEDBLAD
COP3502, 0001

DESCRIPTION: A program that reads in a very large integer and multiplies it.
The file "bigint.txt" will be read. It needs to contain integers in the right format to yield a correct solution.
*/

// Include the necessary packages.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define the SIZE, add one to ten thousand.
# define SIZE 10001

/* Below are all the PRE/POST CONDITIONS. A majority of the PRE/POST conditions cover pretty thoroughly what is
   expected from the below code. I still included some extra comments though.
*/



//Preconditions: the first parameter is string that only
// contains digits and is 10000 digits or
// fewer. No leading 0s will be included
// unless the number represented is 0.
//Postconditions: The function will read the digits of the
// large integer character by character,
// convert them into integers and return a
// pointer to the appropriate struct integer.
struct integer* convert_integer(char* stringInt);

//Preconditions: p is a pointer to a big integer.
//Postconditions: The big integer pointed to by p is
// printed out.
void print(struct integer *p);

//Preconditions: p and q are pointers to struct integers.
//Postconditions: A new struct integer is created that
// stores the product of the integers
// pointed to by p and q and a pointer to it
// is returned.

// MULTIPLY FUNCTION
struct integer* multiply(struct integer *p, struct integer *q);
// This function multiples by TEN, puts ZERO in the least significant place.
struct integer* multiplyByTen(struct integer *p);
// This function frees the struct integer digists by calling the free() function.
void free_struct(struct integer *p);
// Sean's ADDITION fucntion, found on Webcourses alongside the assignment.
struct integer* add(struct integer *p, struct integer *q);

// Below is the struct given to us by Instructor on Webcourses.

struct integer
{
    int* digits;
    int size;
};

/* Below is the main-function, and the FILE-Reader. It takes in the file "bigint.txt"
   Prints the Problem#, the first number to be multiplied, the second number to be multiplied.
   Then it prints a * sign in the middle, and finally the solution stored in c.
*/

int main()
{

    FILE *fp = fopen("bigint2.txt", "r");
    struct integer *o;
    struct integer *s;
    struct integer *c;
    int  i, n;
    char n1[SIZE], n2[SIZE];
    fscanf(fp, "%d", &n);

    for(i = 0; i < n; i++)
    {
        fscanf(fp, "%s%s", &n1, &n2);

        o = convert_integer(n1);
        s = convert_integer(n2);
        c = multiply(o, s);

        printf("Problem #%d: ", i+1);
        print(o);
        printf(" * " );
        print(s);
        printf(" = " );
        print(c);
        printf("\n");


    }
    fclose(fp);

    return EXIT_SUCCESS;
}

/* Multiply Function. Dynamic memory is allocated with malloc, and with calloc a group of objects is allocated.
   New struct integer is created that stores the multiplied (product) integer values pointed to by p and q,
   and a pointer to it is then returned.
*/

struct integer* multiply(struct integer *p, struct integer *q)
{
    struct integer *ans  = malloc(sizeof(struct integer));
    ans->size = p->size + q->size;
    ans->digits = calloc(1, ans->size * sizeof(int));
    struct integer *temp = malloc(sizeof(struct integer));
    temp->size = p->size + q->size;
    temp->digits = calloc(1, temp->size * sizeof(int));
    struct integer *fre;

    int x, y, result, carry = 0;
    for(x = p->size - 1; x >= 0; x--)
    {
        for(y = 0; y < q->size; y++)
        {
            result = (p->digits[x] * q->digits[y] + carry) % 10;
            carry = (p->digits[x] * q->digits[y] + carry) / 10;
            temp->digits[y] = result;
        }
        temp->digits[y] = carry;
        ans = add(ans, temp);
        if(x > 0)
        {

            fre = multiplyByTen(ans);
            free_struct(ans);
            ans = fre;
        }
        carry = 0;
        free(temp->digits);
        temp->digits = calloc(1, temp->size * sizeof(int));
    }

    x = ans->size - 1;
    while(ans->digits[x] == 0 && ans->size > 1)
    {
        ans->size--;
        x--;
    }

    return ans;
}
// Function implemented to multiply by 10, in other words, puts a ZERO in the least significant place.
struct integer* multiplyByTen(struct integer *p)
{
       struct integer *new_int = malloc(sizeof(struct integer));
       int m;
       new_int->size = p->size + 1;
       new_int->digits = malloc(new_int->size * sizeof(int));
       new_int->digits[0] = 0;
       for(m = 0; m < p->size; m++)
       {
            new_int->digits[m+1] = p->digits[m];
       }
       return new_int;
}


// Converts integer from a charachter array to an integer array.
struct integer* convert_integer(char* stringInt)
{
       struct integer *p = malloc(sizeof(struct integer));

       int i;
       p->size = strlen(stringInt);
       p->digits = malloc(p->size * sizeof(int));
       for(i = 0; i < p->size; i++)
       {
             int temp = stringInt[i];
             p->digits[p->size - i -1] = temp - '0';
       }

       return p;
}
// Frees's the struct integer digits by calling free() function.
void free_struct(struct integer *p)
{
    free(p->digits);
    free(p);
}

// The big integer pointed to by P is pointed out.
print(struct integer *p)
{
     int i;
     for(i = p->size - 1; i >= 0; i--)
     {
          printf("%d", p->digits[i]);
     }
}

// Sean's ADDITION function, found on Webcourses.

struct integer* add(struct integer *p, struct integer *q)
{
    struct integer *new_int = malloc(sizeof(struct integer));
    struct integer *temp = NULL;

    int i, d, carry;

    new_int->size = (p->size > q->size) ? p->size : q->size;
    new_int->digits = malloc(sizeof(int) * (new_int->size + 1));

    for (carry = i = 0; i < new_int->size; i++)
    {
        d = ((i < q->size) ? q->digits[i] : 0)
          + ((i < p->size) ? p->digits[i] : 0) + carry;

        new_int->digits[i] = d % 10;
        carry              = d / 10;
    }
    if (carry)
    {
        new_int->digits[i] = carry;
        new_int->size++;
    }

    return new_int;
}
