/*
Katie Bourque
Accumulator II:
This program can convert values between Octal, Hexidecimal, Decimal, and Binary.
It can add, subtract, negate, perform logical operations, and take the
complement of, and shift the Accumulator.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
/*
This method returns the binary string converted to short.
*/
unsigned short get_binary_op(char *bin)
{
  short val = 0;
  int len = (strlen(bin)-1);
  int i; //keeps track of position in array
  int p = 0; //keeps track of power for each position, i

  for (i = len; i >= 0; i--)
  {
    if (bin[i] == '1') {
      val += pow(2, p);
      p++;
    }
  }
  return val;
}

/*
This method converts the decimal value to a binary string
*/
void convert_to_binary (short acc, char *bin)
{
  unsigned short val = acc;
  short i; //keeping track of position
  int len = (strlen(bin)-1);

  for (i = len; i >= 0; i--) { //adds spaces between every 4 integers
    if (i%5 == 4) {
      bin[i] = ' ';
      i--;
    }
    if (val%2 == 0) { //when the remainder is zero, add a zero to the array
      bin[i] = '0';
    }
    else if (val%2 == 1) { //when the remainder is one, add a zero to the array
      bin[i] = '1';
    }
    val = val/2; //each loop, divide the value by 2
  }
}

/*
This method prompts the user for a number input depending on the mode, converts it to hex, octal, or decimal, and prints the value
*/
short get_operand (char mode)
{
  short number; //input value
  char bin_string[20]; //20 spaces for binary representation

  switch(mode)
  {
  case 'O': // if mode is octal
    printf("Enter an Octal Number: ");
    scanf("%ho", &number); // assign the input to acc as octal and echo print
    printf("%ho\n", number); //echo print
    break;

  case 'H': // if mode is hex
    printf("Enter a Hexidecimal Number: ");
    scanf("%hx", &number); // assign the input to acc as hex and echo print
    printf("%hx\n", number); //echo print
    break;

  case 'D': // if mode is decimal
    printf("Enter a Decimal Number: ");
    scanf("%hd", &number); // assign the input to acc as decimal and echo print
    printf("%hd\n", number); //echo print
    break;

  case 'B': //if mode is binary
    printf("Enter a Binary Number: ");
    scanf("%s", bin_string); // assign the input to acc as hex and echo print
    printf("%s\n", bin_string);
    number = get_binary_op(bin_string); //converts binary string to short
    break;
  }
  return number;
}

/*
This method adds the value stored in mode to the accumulator and tells the
user if there is positive or negative overflow.
*/
void add(short *acc, char mode)
{
  short acc_val;
  short op_val;

  acc_val = *acc;
  op_val = get_operand(mode);
  *acc = (acc_val + op_val);

  if (*acc > 0 && acc_val < 0 && op_val < 0){ //negative overflow if both values are negative and sum is positive
    printf("Negative Overflow");
  }
  if (*acc < 0 && acc_val > 0 && op_val > 0){ //positive overflow if both values are positive and sum is negative
    printf("Positive Overflow");
  }
}

/*
This method subtracts the value stored in mode to the accumulator and tells the
user if there is positive or negative overflow.
*/
void subtract(short *acc, char mode)
{
  short acc_val;
  short op_val;

  acc_val = get_operand(mode);
  op_val = *acc;
  *acc = (op_val - acc_val);

  if (*acc > 0 && acc_val < 0 && op_val < 0) {
    printf("Negative Overflow");
  }
  if (*acc > 0 && acc_val < 0 && op_val < 0) {
    printf("Positive Overflow");
  }
}

/*
This method prints the accumulator with the converted values.
*/
void print_acc (short acc)
{
  char binary[20] = "0000 0000 0000 0000"; //default binary value
  convert_to_binary(acc, binary); //convert short to binary

  printf("****************************************\n");
  printf("* Accumulator:                         *\n");
  printf("*   Binary  :  %19s     *\n", binary);
  printf("*   Hex     :  %04hX                    *\n", acc); // all hex numbers will be 4 digits
  printf("*   Octal   :  %06ho                  *\n", acc); // all octal numbers will be 6 digits
  printf("*   Decimal :  %-10hd              *\n", acc); // decimal numbers must be at least 1 digit
  printf("****************************************\n");
  printf("                                        \n");
}

/*
This method prints the menu of options for the user to select and checks for invalid options.
*/
char print_menu (void)
{
    int valid_choice = 0;
    char valids[30] = "BOHDCSQbohdcsq&|^~<>+-Nn"; //valid options
    char choice[5];
    char i;
    char input;
    int counter = 0;

    while(valid_choice != 1)
    {
      printf("Please select one of the following options: \n");
      printf("                                        \n");
      printf("B  Binary Mode              &  AND with Accumulator             + Add to Accumulator\n");
      printf("O  Octal Mode               |  OR  with Accumulator             - Subtract from Accumulator\n");
      printf("H  Hexidecimal Mode         ^  XOR with Accumulator             N Negate Accumulator\n");
      printf("D  Decimal Mode             ~  Complement Accumulator\n");
      printf("                                        \n");
      printf("C  Clear Accumulator        < Shift Accumulator Left\n");
      printf("S  Set Accumulator          > Shift Accumulator Right\n");
      printf("                                        \n");
      printf("Q  Quit\n");
      printf("                                        \n");
      printf("Option: ");
      scanf("%s", choice);
      printf("%s\n", choice);
      //input = choice[0]; //input length

      char invalid[10];
      if (strlen(choice) > 1) {
        for (i = 0; i <= strlen(choice); i++) {
          invalid[i] = choice[i];
          //printf("Invalid Option: %c", choice[i]);
        }
        printf("Invalid Option: %s\n", invalid);
      }

      else {
        input = choice[0];
        for (i = 0; valids[i] != '\0'; i++) { //counts how many characters the input does not match
          if (input != valids[i]) {
            counter = counter + 1;
          //printf("input=%c\n", input);
          //printf("counter=%c\n", valids[i]);
        }
      }
      if (counter >= 24) { //24 possible valid input options
        printf("Invalid Option: %c\n", input); // echo print the invalid option
      }
}

    //printf("counter=%d\n", counter);

  //else {
    //valid_choice = 1;
  //}
  }
    return input;
}


/*
Main program:
This prints the accumulator and the main menu, receives the user input for mode, and either sets the mode, resets the accumulator, or quits the program
*/
int main (void)
{
  short acc = 0; //number input variable
  char mode = 'D'; //mode variable
  char input;
  int loop = 0;
  short left_shift;
  short right_shift;

  while (loop != 1) {
    print_acc(acc);
    input = print_menu();

    switch(input)
    {
      case 'B': //binary mode
      case 'b':
        printf("Mode is Binary\n");
        mode = 'B';
        break;

      case 'O': // octal mode
      case 'o':
        printf("Mode is Octal\n");
        mode = 'O';
        break;

      case 'H': // hex mode
      case 'h':
        printf("Mode is Hexidecimal\n");
        mode = 'H';
        break;

      case 'D': // decimal mode
      case 'd':
        printf("Mode is Decimal\n");
        mode = 'D';
        break;

      case 'C': // clear accumulator
      case 'c':
        acc = 0;
        break;

      case 'S': // set accumulator
      case 's':
        acc = get_operand(mode);
        break;

      case 'Q': // quit
      case 'q':
        loop = 1;
        break;

      case '&': //and
        acc &= get_operand(mode);
        break;

      case '|': //or
        acc |= get_operand(mode);
        break;

      case '^': //XOR
        acc ^= get_operand(mode);
        break;

      case '~': //complement
        acc = ~acc;
        break;

      case '<': //left shift
        printf("Enter number of positions to shift accumulator left by:");
        scanf("%hd", &left_shift);
        printf("%hd", left_shift);
        acc = acc<<left_shift;
        break;


      case '>': //right shift
        printf("Enter number of positions to shift accumulator right by:");
        scanf("%hd", &right_shift);
        printf("%hd", right_shift);
        acc = acc>>right_shift;
        break;

      case '+': //add to accumulator
        add(&acc, mode);
        break;

      case '-': //subtract from accumulator
        subtract(&acc, mode);
        break;

      case 'N': //negate accumulator
      case 'n':
        acc = -acc;
        break;

 }

}
return 0;
}
