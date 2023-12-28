#define VID_MEM 0xb8000



// calculates the vga text-mode address
int get_address(int row,int column){
   return VID_MEM + 2 * (row * 80 + column);
}

// writes string to the video memory (.n) is newline
void print( int colour, const char *string )
{    
    volatile char *video = (volatile char*)0xB8000;
    int row = 1;

    while( *string != 0 )
    {
        if(*string  == '.' && *(string + 1) == 'n')
        {
            video = (char*)get_address(row,0);
            row +=1; 
            string +=2;
            continue;
        }
        else{
        *video++ = *string++;
        *video++ = colour;
        }
    }
}
void puts(int row,int col, char *chr){
    volatile char *video = (volatile char*)0xB8000;

    video = (char*)get_address(row,col);
    *video = *chr;
}

void kernel_start(){
    puts(10,10,"A");
}

