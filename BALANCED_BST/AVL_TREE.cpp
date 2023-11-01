#include"bstAvl.hpp"
#include <iomanip>
int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out_avl.txt", "w", stdout);
    ofstream out;
    out.open("report_avl.txt");
    bstAvl bst;
    char s;
    int n;
    vector<pair<char, int>> query;
    while (!feof(stdin))
    {
        cin >> s;
        if (s != 'T')
            cin >> n;
        query.push_back({s, n});
    }
    if (query.back().first == 'T')
        query.pop_back();
    double ins = 0, del = 0, ser = 0, trav = 0;
    int i=0;
    for (auto v : query)
    {
        // cout<<++i<<endl;
        switch (v.first)
        {
        case 'F':
            // auto start = chrono::high_resolution_clock::now();
            ser+= bst.findWithClock(v.second);
            // auto end = chrono::high_resolution_clock::now();
            // ser+=chrono::duration_cast<chrono::duration<double, milli>>(end - start).count();
            break;
        case 'I':
            ins+= bst.insertWithClock(v.second);
            break;
        case 'D':
            del+=bst.deleteWithClock(v.second);
            break;
        case 'T':
            trav+= bst.traversal();
            break;
        default:
            break;
        }
    }
    out<<setprecision(8);
    out << "Operation time(ms)\n";
    out << "Insert " << ins << endl;
    out << "Delete " << del << endl;
    out << "Search " << ser << endl;
    out << "Trav " << trav << endl;
    out << "Total " << (ins + del + ser + trav) << endl;
    out.close();
}