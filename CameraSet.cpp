#include<bits/stdc++.h>
using namespace std;

int n, ans = 0, maxX = 0, maxY = 0;
struct cam
{
    int x, y, id;
};
vector<cam> camList;
vector<int> trace, path[100010];

bool cmp(cam i, cam j)
{
    return ((abs(i.y) < abs(j.y)) || ((abs(i.y) == abs(j.y))&&(abs(i.x) < abs(j.x))));
    /// sort theo y tang, y bang nhau (cung nhom) thi sort theo x tang
}

int dist(cam A, cam B)
{
    return (abs(A.x - B.x) + abs(A.y - B.y));
}

int cal(cam A, int pos)
{
    /// TH1:
    int minDist, minId = 0, check = 0;
    check = min(abs(A.y), maxY) >= min(abs(A.x), maxX);
    if (A.y == 0) check = 0;
    if (A.x == 0) check = 1;

    if (check)
    {
        /// di tu Oy
        trace[A.id] = -2;
        minDist = abs(A.x);
        maxY = max(maxY, abs(A.y));
    }
    else
    {
        /// di tu Ox
        trace[A.id] = -1;
        minDist = abs(A.y);
        maxX = max(maxX, abs(A.x));
    }

    /// TH2: di tu cac cam co y be hon
    for (int k = 1; k < pos; k ++)
        if (dist(A, camList[k]) < minDist)
        {
            minDist = dist(A, camList[k]);
            minId = camList[k].id;
        }

    if (minId > 0) trace[A.id] = minId;

    return minDist;
}

int main()
{
    //freopen("VD1.INP","r",stdin);
    //freopen("VD1.OUT","w",stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cam tmp;
    cin >> n;
    for (int i = 0; i <= n; i ++)
    {
        tmp.id = i;
        cin >> tmp.x >> tmp.y;
        camList.push_back(tmp);
        trace.push_back(0);
    }

    sort(camList.begin() + 1, camList.end(), cmp);
    //for (auto k: camList) cout << k.x << " " << k.y <<" \t";cout<<"\n";

    for (int Begin = 1; Begin < camList.size(); Begin ++)
    {
        /// moi nhom (cung y): Begin -> End
        int End = Begin;
        for (End = Begin; End < camList.size(); End ++)
            if ((End + 1 == camList.size()) || (camList[End].y != camList[End+1].y)) break;

        int pre, res;
        //cout << Begin << " " << End << "\n";

        /// xet End: cam co x lon nhat nhom
        pre = cal(camList[End], Begin);
        ans += pre;
        //cout << "e "<<trace[camList[End].id] << " -> " << camList[End].id << "\n";

        /// xet Begin: cam co x be nhat nhom
        if (Begin < End)
        {
            res = cal(camList[Begin], Begin);
            if (res > dist(camList[Begin], camList[End]))
                if (trace[camList[End].id] != -2)
                {
                    res = dist(camList[Begin], camList[End]);
                    trace[camList[Begin].id] = camList[End].id;
                    /// di tu End
                }
                else
                {
                    res = 0;
                    trace[camList[Begin].id] = -2;
                    trace[camList[End].id] = camList[Begin].id;
                    /// cung di tu Oy
                }
            else
                if (pre > dist(camList[Begin], camList[End]))
                {
                    /// End di tu Begin neu toi uu
                    ans -= pre;
                    ans += dist(camList[Begin], camList[End]);
                    trace[camList[End].id] = camList[Begin].id;
                }
            //cout << "b "<<trace[camList[Begin].id] << " -> " << camList[Begin].id << "\n";
            ans += res;
        }

        /// xet cac cam con lai: Begin + 1, End - 1, Begin + 2, End - 2, ...
        if ((trace[camList[End].id] == -2) || (trace[camList[End].id] == camList[Begin].id))
            {
                for (int i = Begin + 1; i <= End; i ++)
                    trace[camList[i].id] = Begin;
            }
        else
        {
            int i = Begin + 1, j = End - 1;
            /// xet i tang tu Begin+1 va j giam tu End-1
            /// i toi uu di tu i-1 hoac j+1
            /// j toi uu di tu i hoac j+1
            while (i <= j)
            {
                res = cal(camList[i], Begin);
                if (res > dist(camList[i-1], camList[i]))
                {
                    res = dist(camList[i-1], camList[i]);
                    trace[camList[i].id] = i - 1;
                }
                if (res > dist(camList[i], camList[j+1]))
                {
                    res = dist(camList[i], camList[j+1]);
                    trace[camList[i].id] = j + 1;
                }
                //cout << trace[camList[i].id] << " -> " << camList[i].id << "\n";
                ans += res;

                if (i < j)
                {
                    res = cal(camList[j], Begin);
                    if (res > dist(camList[i], camList[j]))
                    {
                        res = dist(camList[i], camList[j]);
                        trace[camList[j].id] = i;
                    }
                    if (res > dist(camList[j], camList[j+1]))
                    {
                        res = dist(camList[j], camList[j+1]);
                        trace[camList[j].id] = j + 1;
                    }
                    //cout << trace[camList[j].id] << " -> " << camList[j].id << "\n";
                    ans += res;
                }

                i ++;
                j --;
            }
        }
        //cout<<"\n";
        Begin = End;
    }

    ans += maxX + maxY;
    //cout << maxX << " " << maxY <<"\n";
    cout << ans << "\n";
    for (int i = 1; i <= n; i ++)
    {
        if (trace[i] == -1) cout << "Ox";
        if (trace[i] == -2) cout << "Oy";
        if (trace[i] >= 0) cout << trace[i];
        cout << " -> " << i << "\n";
    }

    //for (int i = 1; i <= n; i ++)



    return 0;
}
/*
test 1
6
0 0
1 6
2 0
4 3
3 6
4 0
2 3
ans = 17
15
4 -> 1
Ox -> 2
Ox -> 3
6 -> 4
Ox -> 5
3 -> 6


test 2
10
0 0
2 1
3 0
9 1
7 0
5 7
2 4
8 3
3 5
7 7
9 0
ans = 26
Ox -> 1
Ox -> 2
Ox -> 3
Ox -> 4
9 -> 5
1 -> 6
Ox -> 7
6 -> 8
7 -> 9
Ox -> 10


test 3
7
0 0
0 1
0 3
-3 3
-3 4
-3 7
-4 7
-7 7
ans = 18
Oy -> 1
Oy -> 2
2 -> 3
3 -> 4
Oy -> 5
5 -> 6
5 -> 7


test 4
2
0 0
-2 2
-3 2
ans = 5

*/
