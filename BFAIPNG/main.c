//
//  main.c
//  BFAIPNG
//
//  Created by Aaron Kaufer on 5/29/18.
//  Copyright © 2018 Aaron Kaufer. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    system("echo \"$(script -t 1 /dev/null /Users/AKaufer/Library/Developer/Xcode/DerivedData/BFAIClean-hjmkdnzzadciigavdbvekfwnzlfn/Build/Products/Debug/pngMaker.sh | tee /dev/tty)\"");

    return 0;
}
