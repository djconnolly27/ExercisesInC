#include <stdio.h>
#include <stdlib.h>

/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name) {
  puts(prompt);
  scanf("%2s", card_name);
}

/* Counts cards as they appear during game

  card_name: buffer where card id is stored
  count: current count, determines wager in game
*/
void count_cards(char *card_name, int count) {
  char prompt[22] = "Enter the card_name: ";
  int val = 0;
  while (card_name[0] != 'X') {
    get_card_name(prompt, card_name);
    switch(card_name[0]) {
      case 'K':
      case 'Q':
      case 'J':
        val = 10;
        break;
      case 'A':
        val = 11;
        break;
      case 'X':
        continue;
      default:
        val = atoi(card_name);
        printf("Val: %i\n", val);
        if ((val < 1) || (val > 10)) {
          puts("I don't understand that value!");
          continue;
        }
      }
    if ((val > 2) && (val < 7)) {
      count++;
    } else if (val == 10) {
      count--;
    }
    printf("Current count: %i\n", count);
  }
}

/* Runs card counting simulation
*/
int main()
{
  char card_name[3];
  int count = 0;
  count_cards(card_name, count);
  return 0;
}
