#include<bits/stdc++.h>
using namespace std;

int n, ans;
struct cam
{
    int x, y, id;
};
vector<cam> camList;
vector<int> trace;

bool cmp(cam i, cam j)
{
    return ((i.y < j.y) || ((i.y == j.y)&&(i.x < j.x)));
    /// sort theo y tang, y bang nhau (cung nhom) thi sort theo x tang
}

int dist(cam A, cam B)
{
    return (abs(A.x - B.x) + abs(A.y - B.y));
}

int cal(cam A, int pos)
{
    /// TH1:
    int minDist = min(A.x, A.y), minId = 0;
    if (A.x <= A.y)
    {
        /// di tu Oy
        trace[A.id] = -2;
    }
    else
    {
        /// di tu Ox
        trace[A.id] = -1;
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
        //cout << lastBegin << " " << lastEnd << "   " << Begin << " " << End << "\n";

        /// xet End: cam co x lon nhat nhom
        pre = cal(camList[End], Begin);
        ans += pre;
        //cout << "e "<<trace[camList[End].id] << " -> " << camList[End].id << "\n";

        /// xet Begin: cam co x be nhat nhom
        if (Begin < End)
        {
            res = cal(camList[Begin], Begin);
            if (res > dist(camList[Begin], camList[End]))
            {
                res = dist(camList[Begin], camList[End]);
                trace[camList[Begin].id] = camList[End].id;
                /// di tu End
            }
            else
                if (pre > dist(camList[Begin], camList[End]))
                {
                    /// End di tu Begin neu toi uu
                    ans -= pre;
                    ans += dist(camList[Begin], camList[End]);
                    trace[camList[End].id] = camList[Begin].id;
                    if (trace[camList[Begin].id] == -2) trace[camList[End].id] = -2;
                    /// ca Begin va End deu di tu Oy
                }
            //cout << "b "<<trace[camList[Begin].id] << " -> " << camList[Begin].id << "\n";
            ans += res;
        }

        /// xet cac cam con lai: Begin + 1, End - 1, Begin + 2, End - 2, ...
        if ((trace[camList[End].id] == -2) || (trace[camList[End].id] == camList[Begin].id)
            || (trace[camList[Begin].id] == camList[End].id))
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

    int maxX = 0, maxY = 0;
    for (int i = 1; i <= n; i ++)
    {
        if (trace[camList[i].id] == -2) maxY = max(maxY, camList[i].y);
        if (trace[camList[i].id] == -1) maxX = max(maxX, camList[i].x);
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
ans =
*/
