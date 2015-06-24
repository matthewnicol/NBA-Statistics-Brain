#ifndef PLAY_H
#define PLAY_H

#include <string>

class Play 
{
private:
  Play() {};
  int  len() const { return playtext.size(); };
  char quarter, teamcol;
  std::string teama, teamb;
  int date, timeleft;
  int scorea, scoreb;
public:
  std::string playtext;
  int getTime() const { return timeleft; };
  Play(std::string fname, std::string lineoftext) {
    date = atoi(fname.substr(12, 8).c_str());
    teama = fname.substr(20, 3);
    teamb = fname.substr(23);  
    std::string q, tl, sa, sb, col;

    //iterate through string to get details within. 
    int fields = 0;
    for (int i = 0; i < lineoftext.length(); i++) {
      if (lineoftext.at(i) == ',') { fields++; i++; }
      else if (lineoftext.at(i) == '<' && lineoftext.at(i+1) == 'B' && lineoftext.at(i+2) == '>') { i+=2; } 
      else if (lineoftext.at(i) == '\n') { break; }

      else if (fields == 0) { q += lineoftext.at(i); }
      else if (fields == 1) { tl += lineoftext.at(i); }
      else if (fields == 2) { col += lineoftext.at(i); }
      else if (fields == 3) { playtext += lineoftext.at(i); }
      else if (fields == 4) { sa += lineoftext.at(i); }
      else if (fields == 5) { sb += lineoftext.at(i); }
    } 

    scorea = atoi(sa.c_str());
    scoreb = atoi(sb.c_str());
    teamcol = col.at(0);
    quarter = atoi(q.c_str());
    timeleft = atoi(tl.c_str());
  };

  std::string getTeam()      const { if (teamcol != '2') { return (teamcol == '3') ? teama : teamb; } return "2"; };
  std::string getOtherTeam() const { if (teamcol != '2') { return (teamcol == '3') ? teamb : teama; } return "2"; };
  int qtr() const { return quarter; }

  std::string gameTitle() const { return std::to_string(date) + teama + teamb; };

};

#endif
