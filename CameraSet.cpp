#include<bits/stdc++.h>
using namespace std;

int n, ans = 0;
struct cam
{
    int x, y, id;
};
vector<cam> camList;
vector<int> trace, mid, Next[100010];
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

int cal(cam A, int pos)
{
    /// TH1:
    int minDist, minId = 0, check = 0;

    if (abs(A.x) <= abs(A.y))
    {
        /// di tu Oy
        trace[A.id] = -2;
        minDist = abs(A.x);
    }
    else
    {
        /// di tu Ox
        trace[A.id] = -1;
        minDist = abs(A.y);
    }

    /// TH2: di tu cac cam co y be hon
    for (int k = 1; k < pos; k ++)
        if (dist(A, camList[k]) <= minDist)
        {
            if (dist(A, camList[k]) < minDist)
            {
                minDist = dist(A, camList[k]);
                minId = camList[k].id;
            }
            if (((trace[A.id] == -2)&&(camList[k].x == 0))
                || ((trace[A.id] == -1)&&(camList[k].y == 0)))
                minId = camList[k].id;
        }

    if (minId > 0) trace[A.id] = minId;

    return minDist;
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
        trace.push_back(0);
        mid.push_back(0);
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
            if (res > dist(camList[Begin], camList[End]) + pre)
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
                    trace[camList[i].id] = camList[Begin].id;
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

    int maxX = 0, maxY = 0;
    for (int i = 1; i <= n; i ++)
    {
        if (trace[camList[i].id] == -2) maxY = max(maxY, abs(camList[i].y));
        if (trace[camList[i].id] == -1) maxX = max(maxX, abs(camList[i].x));
    }

    ans += maxX + maxY;
    //cout << maxX << " " << maxY <<"\n";
    cout << ans << "\n";
    for (int i = 1; i <= n; i ++)
    {
        int k = trace[camList[i].id];
        if (k == -1)
        {
            cout << "Tu";
            if (camList[i].y != 0) 
            {
                mid[camList[i].id] = camList[i].x;
                cout << " -> (" << mid[camList[i].id] << ", 0)";
            }
            Next[0].push_back(camList[i].id);
        }
        if (k == -2)
        {
            cout << "Tu";
            if (camList[i].x != 0) 
            {
                mid[camList[i].id] = camList[i].y;
                cout << " -> (0, " << mid[camList[i].id] << ")";
            }
            Next[0].push_back(camList[i].id);
        }
        if (k >= 0)
        {
            cout << "Cam " << k << " (" << camList[k].x << ", " << camList[k].y << ")";
            Next[k].push_back(camList[i].id);
        }
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
ans = 17
Tu -> Cam 2 (2, 0)
Tu -> Cam 5 (4, 0)
Tu -> (0, 3) -> Cam 6 (2, 3)
Cam 6 -> Cam 3 (4, 3)
Tu -> (0, 6) -> Cam 1 (1, 6)
Cam 1 -> Cam 4 (3, 6)

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
ans = 28
Tu -> Cam 3 (3, 0)
Tu -> Cam 4 (7, 0)
Tu -> Cam 10 (9, 0)
Tu -> (2, 0) -> Cam 1 (2, 1)
Cam 10 -> Cam 6 (9, 1)
Tu -> (8, 0) -> Cam 7 (8, 3)
Tu -> (0, 4) -> Cam 2 (2, 4)
Cam 2 -> Cam 8 (3, 5)
Cam 8 -> Cam 5 (5, 7)
Cam 5 -> Cam 9 (7, 7)

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
Tu -> Cam 1 (0, 1)
Tu -> Cam 2 (0, 3)
Cam 2 -> Cam 3 (-3, 3)
Cam 3 -> Cam 4 (-3, 4)
Tu -> (0, 7) -> Cam 5 (-3, 7)
Cam 5 -> Cam 6 (-4, 7)
Cam 5 -> Cam 7 (-7, 7)


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
9

*/
