#include "import.hpp"
#include "CONST.hpp"
#include "classLeo.hpp"
using namespace std;
int myrandom (int i) {return std::rand()%i;}

int main(){
    //begin select * and push_back in List_Leo
    sqlite3 *db;
    char *zErrMsg = 0;
    sqlite3_stmt * pStmt;
    bool error = sqlite3_open("./lingualeo.txt", &db);
    if ( error ) { 
        cout<<"Can't open database: "<<sqlite3_errmsg(db)<<endl; 
	    sqlite3_close(db); 
        return 999;
    }
    
    if (sqlite3_prepare(db, "SELECT * FROM 'MainTable';", -1, &pStmt, NULL)){
        cout<<"sqlite3_prepare: "<<sqlite3_errmsg(db)<<endl; 
        sqlite3_close(db); 
        return 999;
    }
    vector <Leo*> List_Leo;
    while((sqlite3_step(pStmt)) == SQLITE_ROW){
            //sqlite3_column_text(pStmt, COLUMN_ENG)
        Leo *l=new Leo;
        l->eng=reinterpret_cast<const char*>(sqlite3_column_text(pStmt, COLUMN_ENG));
        l->ru=reinterpret_cast<const char*>(sqlite3_column_text(pStmt, COLUMN_RU));
        l->audio=reinterpret_cast<const char*>(sqlite3_column_text(pStmt, COLUMN_AUDIO));
        l->image=reinterpret_cast<const char*>(sqlite3_column_text(pStmt, COLUMN_IMAGE));
        List_Leo.push_back(l);
    };
    //end select * and push_back in List_Leo
    //start shuffle
    std::srand ( (int)time(0));
    random_shuffle ( List_Leo.begin(), List_Leo.end(),myrandom);
    //end shuffle
    
    vector <Leo*>Now_leo;
    Leo* TrueLeo=0;
    Now_leo.emplace_back(List_Leo.back());
    TrueLeo=List_Leo.back();
    List_Leo.pop_back();
    
    for(int i=0;i!=NUMBER_WORD-1;++i){
    Now_leo.push_back(List_Leo.at(rand()%List_Leo.size()));
    };
    random_shuffle ( Now_leo.begin(), Now_leo.end(),myrandom);
    
    cout<<TrueLeo->eng<<endl;
    for(int i=0;i!=NUMBER_WORD;++i){
    cout<<Now_leo.at(i)->ru<<endl; 
    };
    return 0;
}