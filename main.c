#include "main.h"


void clear_segments();
void set_segment_high(uint8_t pin);
void draw(uint8_t num);

/* Main program */
int main(void)
{
    // This is only used for pin initialization
    // further use would lead to confusion
    uint8_t display_pins[] = {
        SEGMENT_A,
        SEGMENT_B,
        SEGMENT_C,
        SEGMENT_D,
        SEGMENT_E,
        SEGMENT_F,
        SEGMENT_G,
        SEGMENT_DP
    };

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Initialize the GPIOB pins
    // Set the button pin to input
    GPIOB->MODER &= ~(0x3 << (BUTTON_PIN*2));
    GPIOB->PUPDR &= ~(0x3 << (BUTTON_PIN*2));
    GPIOB->PUPDR |=  (0x1 << (BUTTON_PIN*2)); // Pull-up resistor

    // Initialize the GPIOA pins
    // Set the Segment pins to output
    for(int i = 0; i < 8; i++)
    {
        uint8_t pin = display_pins[i];
        GPIOA->MODER  &= ~(0x3 << (pin*2));
        GPIOA->MODER  |=  (0x1 << (pin*2));
        GPIOA->OTYPER &= ~(0x1 << pin);
    } 

    uint8_t button_down = 0;
    uint8_t num = 0;
    draw(num);
    while(1)
    {
        // Invert the idr register value, since '0' means 'pressed' ( Button connects to ground )
        uint32_t idr_val = ~GPIOB->IDR;
        if(idr_val & (1 << BUTTON_PIN))
        {
            if(!button_down)
            {
                num++;
                if(num > 9)
                    num = 0;

                draw(num);
            }
            button_down = 1;
        }
        else
        {
            button_down = 0;
        }

    }
}

void clear_segments()
{
    GPIOA->ODR = 0;
}

void set_segment_high(uint8_t pin)
{
    GPIOA->ODR |= (0x1 << pin);
}

void draw(uint8_t num)
{
    switch(num)
    {
        case 1:
            clear_segments();

            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            break;
        case 2:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_G);
            set_segment_high(SEGMENT_E);
            set_segment_high(SEGMENT_D);
            break;
        case 3:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            set_segment_high(SEGMENT_G);
            set_segment_high(SEGMENT_D);
            break;
        case 4:
            clear_segments();
            set_segment_high(SEGMENT_F);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_G);
            set_segment_high(SEGMENT_C);
            break;
        case 5:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_F);
            set_segment_high(SEGMENT_G);
            set_segment_high(SEGMENT_C);
            set_segment_high(SEGMENT_D);
            break;
        case 6:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_F);
            set_segment_high(SEGMENT_G);
            set_segment_high(SEGMENT_E);
            set_segment_high(SEGMENT_D);
            set_segment_high(SEGMENT_C);
            break;
        case 7:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            break;
        case 8:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            set_segment_high(SEGMENT_D);
            set_segment_high(SEGMENT_E);
            set_segment_high(SEGMENT_F);
            set_segment_high(SEGMENT_G);
            break;
        case 9:
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            set_segment_high(SEGMENT_D);
            set_segment_high(SEGMENT_F);
            set_segment_high(SEGMENT_G);
            break;
        default:    // Default is 0
            clear_segments();
            set_segment_high(SEGMENT_A);
            set_segment_high(SEGMENT_B);
            set_segment_high(SEGMENT_C);
            set_segment_high(SEGMENT_D);
            set_segment_high(SEGMENT_E);
            set_segment_high(SEGMENT_F);
            break;
    }
}
