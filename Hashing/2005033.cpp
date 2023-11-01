#include "hashTable.hpp"
string genWord(int length)
{

    if (length < 0)
        return "";
    string ans = "";
    while (length--)
    {
        char ch = ('a' + (rand() % 26));
        ans += ch;
    }
    return ans;
}
string method(char m)
{
    if (m == SEP_CHAIN)
    {
        return "Chaining      ";
    }
    else if (m == DBL_HASH)
    {
        return "Double Hashing";
    }
    else
        return "Custom Probing";
}
vector<string> searchAble(vector<pair<string, ll>> words, ll lower, ll length)
{
    vector<string> ans;
    set<ll> st;
    while (st.size()!=length)
    {
        st.insert(rand()%lower);
    }
    for(auto s:st){
        ans.push_back(words[s].first);
    }
    return ans;
    
}
int main()
{
    ofstream out;
    freopen("in.txt", "r", stdin);
    out.open("report.txt");
    seive();
    hashTable table(10000, 1, SEP_CHAIN);
    // cout<<time(0)<<endl;
    srand(1692383302); //

    ll val = 0;

    vector<pair<string, ll>> words;
    while (val < 10000)
    {
        string word = genWord(rand() % 6 + 5);
        if (table.find(word).first == 0)
        {
            table.insert(word, ++val);
            words.push_back({word, val});
        }
    }
    vector<string> searchlist = searchAble(words,5000,1000); 
    vector<pair<ll, char>> ins;
    ll t = 3, n;
    while (t--)
    {
        n = 5000 * (t == 2) + 10000 * (t == 1) + 20000 * (t == 0);
        ins.push_back({n, SEP_CHAIN});
        ins.push_back({n, DBL_HASH});
        ins.push_back({n, CSTM_PROB});
    }
    ll col = 0, prob = 0;
    out << "||Hashtable size ||  Collision Resolution  ||              Hash 1              ||              Hash 2              ||" << endl;
    out << "||               ||          Method        || # of Collisions | Average Probes || # of Collisions | Average Probes ||" << endl;
    out << "---------------------------------------------------------------------------------------------------------------------" << endl;

    for (int j = 0; j < ins.size(); j++)
    {
        if (j % 3 == 0)
            out << "---------------------------------------------------------------------------------------------------------------------" << endl;
        out << "\t";
        if (j % 3 == 1)
        {
            out << ins[j].first;
        }
        else
        {
            out << "     ";
        }
        col = prob = 0;
        out << "\t\t\t" << method(ins[j].second) << "\t\t\t\t\t";
        hashTable htable1(ins[j].first, 1, ins[j].second);
        for (int i = 0; i < ins[j].first and i < words.size(); i++)
        {
            col += htable1.insert(words[i].first, words[i].second);
            // out<<"here"<<endl;
        }
        for (int i = 0; i < 1000; i++)
        {
            prob += htable1.find(searchlist[i]).second;
        }
        out << col << "\t\t\t" << prob * 1.0 / 1000 << "\t\t\t\t";
        col = prob = 0;
        hashTable htable2(ins[j].first, 2, ins[j].second);
        for (int i = 0; i < ins[j].first and i < words.size(); i++)
        {
            col += htable2.insert(words[i].first, words[i].second);
        }
        for (int i = 0; i < 1000; i++)
        {
            prob += htable2.find(searchlist[i]).second;
        }
        out << col << "\t\t\t" << prob * 1.0 / 1000 << endl;
    }

    // for(int i=0; i<nearPrime(5000); i++){
    //     if(table1.Table[i].size()==0) cnt++;
    // }
    // out<<cnt;
    out.close();
}