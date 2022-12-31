/*
  Hello 2023

  HelloWorld.ino
  
  © 2022 stephan.com
*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define SDA_PIN 5
#define SCL_PIN 6

// U8g2 Contructor (Frame Buffer)
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.42" OLED

#define NUM_EVENTS 114
const char * const events[][3] PROGMEM = {
  { "",       "JANUARY 2022",     ""},
  { "Jan 2 d.", "Richard", "Leakey"},
  { "Jan 6 d.", "Peter", "Bogdanovich"},
  { "Jan 6 d.", "Sydney", "Poitier"},
  { "Jan 7",  "COVID-19 cases",   "> 300 million"},
  { "Jan 10", "1st pig->human",   "heart transplant" },  
  { "Jan 12 d.", "Ronnie", "Spector"},
  { "Jan 16", "Tennis douche",    "Djokovic Deported"},
  { "Jan 20 d.", "Meat Loaf", "awww bitch tits :("},
  { "Jan 23", "Trop. Storm Ana",  "kills 115"},
  { "Jan 23 d.", "Thierry", "Mugler"},
  { "Jan 28", "COVID-19 vaxings", "> 10 billion"},
  { "",       "FEBRUARY 2022",     ""},
  { "Feb 3",  "China & Russia",   "Oppose NATO"},
  { "Feb 4-20", "Beijing",        "Winter Olympics"},
  { "Feb 7 d.", "Douglas", "Trumbull"},
  { "Feb 9",  "Fusion breakthru", "5s @ 59Mj = 11Mw"},
  { "Feb 23", "stephan.com (me)", "has birthday"},
  { "Feb 24", "Russia invades",   "Ukraine"},
  { "Feb 26", "EU/US/&c remove",  "Russia from SWIFT"},
  { "Feb 27", "Belarus permits",  "Russian troops"},
  { "Feb 28", "FIFA & UEFA",      "Suspend Russia"},
  { "",       "MARCH 2022",       ""},
  { "March 1", "UN deplores",     "Russian invasion"},
  { "March 2", "Russia siezes",   "Kherson"},
  { "March 3", "Russia attacks",  "Zaporishzhia"},
  { "March 5", "Endurance wreck", "found Antartica"},
  { "March 7", "COVID-19 deaths", "> 6 million"},
  { "March 8", "US & UK ban all", "oil from Russia"},
  {"March 13 d.", "William", "Hurt"},
  { "March 16", "Russia strikes", "Meriupol Theater"},
  { "March 24", "NATO deploys",   "40k troops"},
  { "March 29", "DR Congo joins", "East Africa"},
  { "March 31", "Dubai Expo 2020", "Closes late"},
  { "",         "APRIL 2022",       ""},
  { "April 4",  "IPCC warns green", "house emissions"},
  { "April 6",  "1st Chicxulub",  "fossil reported"},
  { "April 7",  "UN votes 93-24",   "suspend Russia"},
  { "April 13", "COVID-19 cases",   "> 500 million"},
  { "April 14", "Ukraine sinks",  "the Moskva"},
  { "April 18", "Battle of Donbas", "begins"},
  { "April 20", "micronovae",       "discovered"},
  { "April 22", "LHC resumes ops",  "after 3y upgrade"},
  { "April 27", "Gazprom cuts off", "Poland/Bulgaria"},
  { "",         "MAY 2022",       ""},
  { "May 6",    "Monkeypox",        "outbreak"},
  { "May 12",   "Sagittarius A*",   "First images"},
  { "May 14",   "Ukraine wins",     "Eurovision"},
  { "May 16",   "Russia wins",      "Mariupol siege"},
  {"May 17 d.", "Vangelis", ""},
  {"May 26 d.", "Ray", "Liotta"},
  { "",         "JUNE 2022",        ""},
  { "June 14",  "Canada & Denmark", "end Whiskey War"},
  { "June 22",  "6.2 quake kills",  "1100+ afgh/paki"},
  { "June 26",  "G7 meets, bans",   "Russian gold"},
  { "June 28",  "NATO summit held", "Madrid re Russia"},
  { "",         "JULY 2022",        ""},
  {"July 6 d.", "James", "Caan"},
  { "July 8",    "Shinzo Abe",       "assassinated"},
  { "July 11",   "James Webb shows", "galaxy cluster"},
  {"July 18 d.", "Claes", "Oldenburg"},
  { "July 19",   "European",         "heat wave"},
  { "July 21",   "EU central bank",  "raises rate to 0%%"},
  { "July 23",   "WHO declares",     "monkeypox bad"},
  {"July 26 d.", "James", "Lovelock"},
  { "",          "AUGUST 2022",      ""},
  { "Aug 4",     "China wargames",   "because Pelosi"},
  {"Aug 5 d.", "Issey", "Miyake"},
  {"Aug 8 d.", "Dame Olivia", "Newton-John"},
  { "Aug 12",    "Salman Rushie",    "stabbed"},
  { "Aug 17",    "Turkey & Israel",  "kiss & make up"},
  { "Aug 28",    "Pakistan floods",  "fucked again"},
  { "Aug 28",    "Burning Man",  ""},
  {"Aug 30 d.", "Mikhail", "Gorbachev"},
  { "",          "SEPTEMBER 2022",   ""},
  { "Sep 2",     "G7 imposes price", "cap on Russia oil"},
  {"Sep 2 d.", "Frank", "Drake"},
  { "Sep 6",     "Liz Truss UK PM",  "briefly"},
  { "Sep 8",     "QEII dies at 96",  "Britain mourns"},
  { "Sep 8 d.",  "Rori",  "Cronin-Schneider"},
  {"Sep 13 d.", "Jean-Luc", "Godard"},
  { "Sep 14-25", "Hurricane Fiona",  "fucks Puerto Rico"},
  { "Sep 16",    "Mahsa Amini dead", "in Iran b/c hijab"},
  { "Sep 19",    "QEII buried",      "Britain mourns"},
  { "Sep 21",    "Putin mobilizes",  "remaining idiots"},
  { "Sep 26",    "NASA's DART",      "hits Dimorphos"},
  { "Sep 27-30", "Hurricane Ian",    "fucks Cuba & US"},
  { "Sep 27",    "Russia fakes",     "annex referendum"},
  {"Sep 28 d.", "Coolio", ""},
  { "Sep 30",    "Putin signs",      "bullshit papers"},
  { "",          "OCTOBER 2022",   ""},
  {"Oct 4 d.", "Loretta", "Lynn"},
  { "Oct 8",     "Someone bombs",    "Crimean Bridge"},
  {"Oct 11 d.", "Dame Angela", "Lansbury"},
  {"Oct 13 d.", "James", "McDivitt"},
  {"Oct 14 d.", "Robbie", "Coltrane"},
  { "Oct 16-23", "Xi Jinping gets",  "third term"},
  { "Oct 25",    "Rishi Sunak UK PM",  "less briefly"},
  { "Oct 28",    "Elon Musk",        "buys Twitter"},
  {"Oct 28 d.", "Jerry Lee", "Lewis"},
  { "",          "NOVEMBER 2022",   ""},
  {"Nov 8 d.", "Lee", "Bontecou"},
  { "Nov 11",    "FTX goes tits up", "SBF shrugs"},
  { "Nov 11",    "Ukraine regains",  "Kherson"},
  { "Nov 15",    "World population", "Hits 8 billion"},
  { "Nov 16",    "NASA SLS launch",  "Artemis II/Orion"},
  {"Nov 17 d.", "Fred", "Brooks"},
  { "Nov 20",    "FIFA World Cup",   "Starts in Qatar"},
  { "",          "DECEMBER 2022",   ""},
  {  "Dec 5",    "FUSION",           "ignition!"},
  {  "Dec 7",    "China eases",      "COVID restrictions"},
  { "Dec 18",    "FIFA World Cup",   "Argentina wins!"},
  {"Dec 29 d.", "Pelé", ""},
  {"Dec 29 d.", "Dame Vivienne", "Westwood"},
  {"Dec 30 d.", "Barbara", "Walters"},
  {"Dec 31 d.", "Pope Benedict", "XVI"},
};

int event = 0;
unsigned long start_millis;
unsigned long current_millis;
unsigned long period = 1000;
int mode = 0;
int hny = 0;

void setup(void) {
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
  start_millis = millis();
}

void loop(void) {
  char linebuf[20]; // 16 should be enough?
  current_millis = millis();
  if(current_millis - start_millis < period) { return; }

  u8g2.clearBuffer(); // clear the internal memory

  if (mode == 0) {
    period = 5000;
    u8g2.setFont(u8g2_font_adventurer_tr);	
    strcpy_P(linebuf, events[event][0]);
    u8g2.drawStr(5,12, linebuf);
    u8g2.setFont(u8g2_font_efraneextracondensed_te);  
    strcpy_P(linebuf, events[event][1]);
    u8g2.drawStr(0,25, linebuf);
    strcpy_P(linebuf, events[event][2]);
    u8g2.drawStr(0,40, linebuf);
    event = (event + 1) % NUM_EVENTS;
    mode = 1;
  } else {
    u8g2.setFont(u8g2_font_mystery_quest_24_tr);  
    period = 1000;

    if (hny == 0) {
      u8g2.drawStr( 4,30, "Happy");    
    } else if (hny == 1) {
      u8g2.drawStr(15,30, "new");
    } else if (hny == 2) {
      u8g2.drawStr(11,30, "year");
    } else {
      u8g2.setFont(u8g2_font_mystery_quest_32_tr);  
      u8g2.drawStr(3,35, "2023");
      mode = 0;      
    }

    hny = (hny + 1) % 4;
  }

  u8g2.sendBuffer();					// transfer internal memory to the display
  start_millis = current_millis;
}
