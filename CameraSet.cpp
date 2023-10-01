#include<bits/stdc++.h>
using namespace std;

int n, ans = 0, maxX = 0, maxY = 0, preMaxX = 0, preMaxY = 0, preX = 0, preY = 0;
struct cam
{
    int x, y, id;
};
vector<cam> camList;
vector<int> trace, mid, newId, Next[100010];
bool kt[100010];

bool cmp(cam i, cam j)
{
    return ((abs(i.y) < abs(j.y)) || ((abs(i.y) == abs(j.y))&&(abs(i.x) < abs(j.x))));
    /// sort theo y tang, y bang nhau (cung nhom) thi sort theo x tang
}

int dist(cam A, cam B)
{
    return (abs(A.x - B.x) + abs(A.y - B.y));
}

void upmid(int pos, int x, int y)
{
    if (mid[camList[pos].id] == -1)
    {
        int k = camList.size();
        trace.push_back(-1);
        newId[k] = k;
        camList.push_back({x, y, k});
        mid[camList[pos].id] = k;
    }
    else
        {
            camList[mid[camList[pos].id]].x = x;
            camList[mid[camList[pos].id]].y = y;
        }

    trace[mid[camList[pos].id]] = trace[camList[pos].id];
}

int cal(int pos, int posBegin)
{
    int minDist = INT_MAX, minId = 0, check = 0;
    cam A = camList[pos];

    /// TH1:
    if ((min(maxY, abs(A.y)) >= min(maxX, abs(A.x))) && (abs(A.x) + abs(A.y) - min(maxY, abs(A.y)) < minDist)
    && ((abs(A.x) + abs(A.y) - min(maxY, abs(A.y)) < abs(camList[pos].x - camList[posBegin].x)) || (posBegin == 1) || (pos == posBegin)))
    {
        /// di tu Oy
        trace[A.id] = -2;
        minDist = abs(A.x) + abs(A.y) - min(maxY, abs(A.y));
        if ((A.x != 0) && (A.y != 0))
            upmid(pos, 0, A.y);
    }

    if ((min(maxX, abs(A.x)) > min(maxY, abs(A.y))) && (abs(A.x) + abs(A.y) - min(maxX, abs(A.x)) < minDist) 
    && ((abs(A.x) + abs(A.y) - min(maxX, abs(A.x)) < abs(camList[pos].x - camList[posBegin].x)) || (posBegin == 1) || (pos == posBegin)))
    {
        /// di tu Ox
        trace[A.id] = -1;
        minDist = abs(A.x) + abs(A.y) - min(maxX, abs(A.x));
        if ((A.x != 0) && (A.y != 0))
            upmid(pos, A.x, 0);
    }

    /// TH2: di tu cac cam co y be hon
    bool checkX = 0, checkY = 0;
    for (int k = 1; k < posBegin; k ++)
        //if ((k < posBegin) || (k > n))
        {
            if (dist(A, camList[k]) == minDist)                     /// k tren duong di tu Tu den cam 
            {
                if ((trace[A.id] == -2) && (camList[k].x == 0))     /// k tren Oy
                {
                    checkY = 1;
                    trace[A.id] = camList[k].id;
                    if ((camList[k].x != A.x) && (camList[k].y != A.y))
                        upmid(pos, 0, A.y);
                }
                if ((trace[A.id] == -1) && (camList[k].y == 0))     /// k tren Ox
                {
                    checkX = 1;
                    trace[A.id] = camList[k].id;
                    if ((camList[k].x != A.x) && (camList[k].y != A.y))
                        upmid(pos, A.x, 0);
                }
            }
            if (dist(A, camList[k]) < minDist)
            {
                minDist = dist(A, camList[k]);
                trace[A.id] = camList[k].id;
                checkX = 0;
                checkY = 0;
            }        
        }

    if ((trace[A.id] == -2) || (checkY))
    {
        if (abs(A.y) >= maxY)
        {
            preY = preMaxY;
            preMaxY = maxY;
            maxY = abs(A.y);
        }
        else
            if (abs(A.y) > preMaxY)
            {
                preY = preMaxY;
                preMaxY = abs(A.y);
            }
            else preY = max(preY, abs(A.y));

        if (A.y == 0)
        {
            if (abs(A.x) >= maxX)
            {
                preX = preMaxX;
                preMaxX = maxX;
                maxX = abs(A.x);
            }
            else
                if (abs(A.x) > preMaxX)
                {
                    preX = preMaxX;
                    preMaxX = abs(A.x);
                }
                else preX = max (preX, abs(A.x));
        }
    }

    if ((trace[A.id] == -1) || (checkX))
    {
        if (abs(A.x) >= maxX)
        {
            preX = preMaxX;
            preMaxX = maxX;
            maxX = abs(A.x);
        }
        else
            if (abs(A.x) > preMaxX)
            {
                preX = preMaxX;
                preMaxX = abs(A.x);
            }
            else preX = max (preX, abs(A.x));        

        if (A.x == 0)
        {
            if (abs(A.y) >= maxY)
            {
                preY = preMaxY;
                preMaxY = maxY;
                maxY = abs(A.y);
            }
            else
                if (abs(A.y) > preMaxY)
                {
                    preY = preMaxY;
                    preMaxY = abs(A.y);
                }
                else preY = max (preY, abs(A.y));
        }
    }

    return minDist;
}

int cal2(int pos, int left, int right, int posBegin)
{
    /// TH1: di tu cac cam co y be hon
    int minDist = INT_MAX, minId = 0, check = 0;
    cam A = camList[pos];

    for (int k = 1; k < posBegin; k ++)
        if (dist(A, camList[k]) < minDist)
        {
            minDist = dist(A, camList[k]);
            trace[A.id] = camList[k].id;
        }

    /// TH2:
    if ((min(maxX, abs(A.x)) > min(maxY, abs(A.y))) && (abs(A.x) + abs(A.y) - min(maxX, abs(A.x)) < minDist) 
    && (abs(A.x) + abs(A.y) - min(maxY, abs(A.y)) < abs(camList[pos].x - camList[right].x))
    && (abs(A.x) + abs(A.y) - min(maxY, abs(A.y)) < abs(camList[pos].x - camList[left].x)))
    {
        /// di tu Ox
        trace[A.id] = -1;
        minDist = abs(A.x) + abs(A.y) - min(maxX, abs(A.x));
        if (abs(A.x) >= maxX)
        {
            preX = preMaxX;
            preMaxX = maxX;
            maxX = abs(A.x);
        }
        else
            if (abs(A.x) > preMaxX)
            {
                preX = preMaxX;
                preMaxX = abs(A.x);
            }
            else preX = max (preX, abs(A.x));    
        return minDist;    
    }

    if (abs(camList[pos].x - camList[right].x) < abs(camList[pos].x - camList[left].x))
    {
        trace[A.id] = camList[right].id;
        return abs(camList[pos].x - camList[right].x);
    }

    trace[A.id] = camList[left].id;
    return abs(camList[pos].x - camList[left].x);
}

void dfs(int u, int start)
{
    for (int i = 1; i <= start; i ++) cout << " ";
    cout << u << "\n";

    for (int v: Next[u])
        if (!kt[v])
        {
            dfs(v, start + 1);
            kt[v] = 1;
        }
}

int main()
{
    freopen("CameraSet.inp","r",stdin);
    freopen("CameraSet.out","w",stdout);
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
        newId.push_back(0);
        trace.push_back(0);
        mid.push_back(-1);
    }

    sort(camList.begin() + 1, camList.end(), cmp);
    for (int i = 1; i <= n; i ++) newId[camList[i].id] = i;
    //for (auto k: camList) cout << k.x << " " << k.y <<" \t";cout<<"\n";

    for (int Begin = 1; Begin <= n; Begin ++)
    {
        /// moi nhom (cung y): Begin -> End
        int End = Begin;
        for (End = Begin; End <= n; End ++)
            if ((End + 1 == n + 1) || (camList[End].y != camList[End+1].y)) break;

        //cout << Begin << " " << End << "\n";

        if (Begin == 1)
        {
            ans = dist(camList[0], camList[End]);
            trace[camList[Begin].id] = -2;
            for (int i = Begin + 1; i <= End; i ++)
                trace[camList[i].id] = camList[i - 1].id;

            if (camList[Begin].x == 0) maxY = abs(camList[Begin].y);
            if (camList[Begin].y == 0) maxX = abs(camList[End].x);
            //cout<<ans<<"   "<<maxX<<" "<<maxY<<"\n\n";
            Begin = End;
            continue;
        }   

        /// xet End: cam co x lon nhat nhom
        int pre, res;
        pre = cal(End, Begin);
        ans += pre;
        //cout << "end, ="<< pre << " " << trace[camList[End].id] << " -> " << camList[End].id << "\n";

        /// xet Begin: cam co x be nhat nhom
        if (Begin < End)
        {
            res = cal(Begin, Begin);
            //cout << "begin, ="<< res << " " << trace[camList[Begin].id] << " -> " << camList[Begin].id << "\n";

            if (res > dist(camList[Begin], camList[End]) + pre)
                if (trace[camList[End].id] != -2)
                {
                    if (trace[camList[Begin].id] < 0)
                        if ((trace[camList[Begin].id] == -2) && (camList[Begin].x != 0))
                        {
                            res -= maxY;
                            res += preMaxY;
                            maxY = preMaxY;
                            preMaxY = preY;
                        }
                        else
                        {
                            res -= maxX;
                            res += preMaxX;
                            maxX = preMaxX;
                            preMaxX = preX;
                        }

                    res = dist(camList[Begin], camList[End]);
                    trace[camList[Begin].id] = camList[End].id;
                    //cout << "change1" << "\n";                    
                    /// di tu End
                }
                else
                {
                    res = 0;
                    if (trace[camList[Begin].id] == -1)
                    {
                        maxX = preMaxX;
                        preMaxX = preX;
                    }
                    trace[camList[Begin].id] = -2;
                    trace[camList[End].id] = camList[Begin].id;
                    //cout << "change2" << "\n";
                    /// cung di tu Oy
                }
            else
                if (pre > dist(camList[Begin], camList[End]))
                {
                    /// End di tu Begin neu toi uu
                    ans -= pre;
                    ans += dist(camList[Begin], camList[End]);           
                    trace[camList[End].id] = camList[Begin].id;
                    //cout << "change3" << "\n";
                }
            ans += res;

            /// xet cac cam con lai: Begin + 1, End - 1, Begin + 2, End - 2, ...
            if ((trace[camList[End].id] == -2) || (trace[camList[End].id] == camList[Begin].id) || (trace[camList[Begin].id] == camList[End].id))
            {                
                for (int i = Begin + 1; i <= End; i ++)
                    trace[camList[i].id] = camList[i - 1].id;
            }
            else
            {
                int i = Begin + 1, j = End - 1;
                /// xet i tang tu Begin+1 va j giam tu End-1
                /// i toi uu di tu i-1 hoac j+1
                /// j toi uu di tu i hoac j+1
                while (i <= j)
                {
                    res = cal2(i, i - 1, j + 1, Begin);
                    ans += res;

                    if (i < j)
                    {
                        res = cal2(j, i, j + 1, Begin);
                        ans += res;
                    }

                    i ++;
                    j --;
                }
            }
        }
        
        //cout<<ans<<"   "<<maxX<<" "<<maxY<<"\n\n";
        Begin = End;
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i ++)
    {
        int k = trace[camList[i].id];
        if (k < 0)
        {
            cout << "Tu";
            Next[0].push_back(camList[i].id);
        }
        if (k >= 0)
        {
            cout << "Cam " << k << " (" << camList[newId[k]].x << ", " << camList[newId[k]].y << ")";
            Next[k].push_back(camList[i].id);
        }

        if ((mid[camList[i].id] != -1) && ((camList[mid[camList[i].id]].x != camList[i].x) || (camList[mid[camList[i].id]].y != camList[i].y)))
            cout << " -> (" << camList[mid[camList[i].id]].x << ", " << camList[mid[camList[i].id]].y << ")";
        cout << " -> Cam " << camList[i].id << " (" << camList[i].x << ", " << camList[i].y << ")\n";
    }

    cout << "\n";
    dfs(0, 0);

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
ans = 15
Tu -> Cam 2 (2, 0)
Cam 2 (2, 0) -> Cam 5 (4, 0)
Cam 2 (2, 0) -> Cam 6 (2, 3)
Cam 6 (2, 3) -> Cam 3 (4, 3)
Cam 6 (2, 3) -> Cam 1 (1, 6)
Cam 1 (1, 6) -> Cam 4 (3, 6)

test 2
10
0 0
2 1
2 4
3 0
7 0
5 7
9 1
8 3
3 5
7 7
9 0
ans = 25
Tu -> Cam 3 (3, 0)
Cam 3 (3, 0) -> Cam 4 (7, 0)
Cam 4 (7, 0) -> Cam 10 (9, 0)
Tu -> (2, 0) -> Cam 1 (2, 1)
Cam 10 (9, 0) -> Cam 6 (9, 1)
Cam 6 (9, 1) -> Cam 7 (8, 3)
Cam 1 (2, 1) -> Cam 2 (2, 4)
Cam 2 (2, 4) -> Cam 8 (3, 5)
Cam 8 (3, 5) -> Cam 5 (5, 7)
Cam 5 (5, 7) -> Cam 9 (7, 7)

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
ans = 14
Tu -> Cam 1 (0, 1)
Cam 1 (0, 1) -> Cam 2 (0, 3)
Cam 2 (0, 3) -> Cam 3 (-3, 3)
Cam 3 (-3, 3) -> Cam 4 (-3, 4)
Cam 4 (-3, 4) -> Cam 5 (-3, 7)
Cam 5 (-3, 7) -> Cam 6 (-4, 7)
Cam 6 (-4, 7) -> Cam 7 (-7, 7)

test 4
2
0 0
-2 2
-3 2
ans = 5

test 5
7
0 0
0 -1
0 -2
0 -4
0 -5
0 -7
1 -3
1 -4
ans = 9

test 6
8
0 0
0 1
0 3 
-6 0
-6 2
-3 3
-3 4
-5 3
-5 4
ans = 17

*/
