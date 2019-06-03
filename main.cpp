#include <QCoreApplication>
#include <QDebug>
#include <QtGlobal>
#include <QString>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "mfrc522/MFRC522.h"

MFRC522 mfrc522 = MFRC522();
MFRC522::StatusCode status; //variable to get card status

uint8_t buffer[18];  //data transfer buffer (16+2 bytes data+CRC)
uint8_t size = sizeof(buffer);

uint8_t pageAddr = 0x06;  //In this example we will write/read 16 bytes (page 6,7,8 and 9).
                          //Ultraligth mem = 16 pages. 4 bytes per page.
                          //Pages 0 to 4 are for special functions.

int main(int argc, char *argv[])
{
    //MFRC522 mfrc522(1,1);
    //MFRC522 *mfrc522 = new MFRC522(1,1);
    QCoreApplication a(argc, argv);


    wiringPiSPISetup(0, 125000);
    delay(100);

    qDebug() << "test 2 \r\n";
    wiringPiSetup() ;
    pinMode (1, OUTPUT) ;   // LED CS
    delay(100);
    digitalWrite(1, HIGH);
    digitalWrite(1, LOW);
    delay(100);

    pinMode (24, OUTPUT) ;  // reader RST
    delay(1000);
    digitalWrite(24, HIGH);

    pinMode (20, OUTPUT);
    delay(100);
    digitalWrite(20, LOW);

    mfrc522.PCD_Init();

    memcpy(buffer,"HELLO WORLD! ;-)",16);

    qDebug() << "pred while \r\n";

    while(1)
    {
#if 0
        // Look for new cards
          if (mfrc522.PICC_IsNewCardPresent())
          {
              /*qDebug("Card present \r\n");*/
              // Select one of the cards
              if (mfrc522.PICC_ReadCardSerial())
              {
                  mfrc522.WriteUID();
                  qDebug("Card select \r\n");
                  // Write data ***********************************************
                  for (int i=0; i < 4; i++) {
                    //data is writen in blocks of 4 bytes (4 bytes per page)
                    status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(pageAddr+i, &buffer[i*4], 4);
                    if (status != MFRC522::STATUS_OK) {
                      qDebug(("MIFARE_Write() failed: "));
                      qDebug(qPrintable(mfrc522.GetStatusCodeName(status)));
                      break;
                    }
                  }
                  if (status == MFRC522::STATUS_OK)
                  {
                      // Read data ***************************************************
                      qDebug("Reading data ... ");
                      //data in 4 block is readed at once.
                      status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pageAddr, buffer, &size);
                      if (status != MFRC522::STATUS_OK) {
                        qDebug("MIFARE_Read() failed: ");
                        qDebug(qPrintable(mfrc522.GetStatusCodeName(status)));
                      }
                      else
                      {
                          qDebug("Readed data: ");
                          //Dump a byte array to Serial
                          for (uint8_t i = 0; i < 16; i++) {
                            qDebug("%d", buffer[i]);
                          }
                      }
                      qDebug("\r\n");
                  }
              }
          }
          mfrc522.PICC_HaltA();
#endif
          // Look for new cards
          if (mfrc522.PICC_IsNewCardPresent()) {
              //qDebug("Card present \r\n");
              // Select one of the cards
              if (mfrc522.PICC_ReadCardSerial()) {
                  qDebug("Read serial\r\n");
                  // Dump debug info about the card. PICC_HaltA() is automatically called.
                  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
              }
          }
    };

    /*digitalWrite(1, HIGH);
    delay(100);

    //int spi = spi_init("/dev/spidev0.0");
    qDebug() <<"zkous 2 vka";

    uint8_t to_send[] = {0x0, 0x0, 0x0, 0x0};
    qDebug() <<"before send 1";
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 1";

    to_send[0] = 0xe1;
    to_send[1] = 0x0;
    to_send[2] = 0x0;
    to_send[3] = 0x0;
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 2";
    to_send[0] = 0xf1;
    to_send[1] = 0xa1;
    to_send[2] = 0x21;
    to_send[3] = 0x0;
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 3";
    to_send[0] = 0xfe;
    to_send[1] = 0x0;
    to_send[2] = 0x32;
    to_send[3] = 0x11;
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 4";
    to_send[0] = 0xe6;
    to_send[1] = 0x0;
    to_send[2] = 0x0;
    to_send[3] = 0x12;
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 5";

    to_send[0] = 0xff;
    to_send[1] = 0xff;
    to_send[2] = 0xff;
    to_send[3] = 0xff;
    wiringPiSPIDataRW(0, to_send, 4);
    //spi_send(to_send, 4, spi);
    qDebug() <<"after send 6";*/


    return a.exec();
}
