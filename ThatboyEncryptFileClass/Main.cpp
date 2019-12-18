#include "ThatboyEncrypt.h"
#include <iostream>
#include "LZW.h"

#include <iostream>
#include "Base64.h"

int main(int argc, char** argv)
{
    thatboy::EncryptFileStream::Encrypt("MC ball.png", "MC.tef","12345678");

    thatboy::EncryptFileStream::Decrypt("MC.tef", "","12345678");


}

