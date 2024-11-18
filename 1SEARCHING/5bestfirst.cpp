#include <bits/stdc++.h>
using namespace std;

int findIdx(char ch) {
    if (ch == ' ') return 26;
    else if (ch == '.') return 27;
    else return ch - 'a';
}

char findCh(int j) {
    if (j == 26) return ' ';
    else if (j == 27) return '.';
    else return j + 'a';
}

void buildGraph(const string &text, vector<vector<int>> &adj) {
    for (int i = 0; i < text.length() - 1; i++) {
        int id1 = findIdx(text[i]);
        int id2 = findIdx(text[i + 1]);
        adj[id1][id2] += 1;
    }
}

void exploreTransitions(int startIdx, const vector<vector<int>> &adj, priority_queue<pair<int, string>> &pq, vector<vector<int>> &visited) {
    string temp(1, findCh(startIdx)); // Create a string with a single character
    for (int i = 0; i < adj[startIdx].size(); i++) {
        if (adj[startIdx][i] != 0 && !visited[startIdx][i]) {
            string newTransition = temp + findCh(i);
            pq.push(make_pair(adj[startIdx][i], newTransition));
            visited[startIdx][i] = 1;
        }
    }
}

void bestFirstSearch(int startIdx, const vector<vector<int>> &adj, vector<string> &finalAns) {
    priority_queue<pair<int, string>> pq;
    vector<vector<int>> visited(28, vector<int>(28, 0));
    
    exploreTransitions(startIdx, adj, pq, visited);
    
    while (!pq.empty() && pq.top().second.back() != '.') {
        string temp = pq.top().second;
        pq.pop();
        string transition = string(1, temp[0]) + "->" + string(1, temp[1]);
        finalAns.push_back(transition);
        
        int idx = findIdx(temp[1]);
        exploreTransitions(idx, adj, pq, visited);
    }
}

int main() {
    string text = "Everything was in confusion in the Oblonskys house. The wife had "
                   "discovered that the husband was carrying on an intrigue with a French "
                   "girl who had been a governess in their family and she had announced to "
                   "her husband that she could not go on living in the same house with him. "
                   "This position of affairs had now lasted three days and not only the "
                   "husband and wife themselves but all the members of their family and "
                   "household were painfully conscious of it. Every person in the house "
                   "felt that there was no sense in their living together and that the "
                   "stray people brought together by chance in any inn had more in common "
                   "with one another than they the members of the family and household of "
                   "the Oblonskys. The wife did not leave her own room the husband had not "
                   "been at home for three days. The children ran wild all over the house "
                   "the English governess quarreled with the housekeeper and wrote to a "
                   "friend asking her to look out for a new situation for her the mancook "
                   "had walked off the day before just at dinner time the kitchenmaid and "
                   "the coachman had given warning."

                   "Three days after the quarrel Prince Stepan Arkadyevitch "
                   "Oblonsky Stiva as he was called in the fashionable world woke up at "
                   "his usual hour that is at eight oclock in the morning not in his "
                   "wifes bedroom but on the leathercovered sofa in his study. He turned "
                   "over his stout wellcaredfor person on the springy sofa as though he "
                   "would sink into a long sleep again he vigorously embraced the pillow on "
                   "the other side and buried his face in it but all at once he jumped up "
                   "sat up on the sofa and opened his eyes."

                   "Stepan Arkadyevitchs eyes twinkled gaily and he pondered with a smile. "
                   "There was a great deal more that was "
                   "delightful only theres no putting it into words or even expressing it "
                   "in ones thoughts awake. And noticing a gleam of light peeping in "
                   "beside one of the serge curtains he cheerfully dropped his feet over "
                   "the edge of the sofa and felt about with them for his slippers a "
                   "present on his last birthday worked for him by his wife on goldcolored "
                   "morocco. And as he had done every day for the last nine years he "
                   "stretched out his hand without getting up towards the place where his "
                   "dressinggown always hung in his bedroom. And thereupon he suddenly "
                   "remembered that he was not sleeping in his wifes room but in his "
                   "study and why the smile vanished from his face he knitted his brows."

                   "Most unpleasant of all was the first minute when on coming happy and "
                   "goodhumored from the theater with a huge pear in his hand for his "
                   "wife he had not found his wife in the drawingroom to his surprise had "
                   "not found her in the study either and saw her at last in her bedroom "
                   "with the unlucky letter that revealed everything in her hand."

                   "She his Dolly forever fussing and worrying over household details and "
                   "limited in her ideas as he considered was sitting perfectly still with "
                   "the letter in her hand looking at him with an expression of horror "
                   "despair and indignation."

                   "And at this recollection Stepan Arkadyevitch as is so often the case "
                   "was not so much annoyed at the fact itself as at the way in which he had "
                   "met his wifes words."

                   "There happened to him at that instant what does happen to people when "
                   "they are unexpectedly caught in something very disgraceful. He did not "
                   "succeed in adapting his face to the position in which he was placed "
                   "towards his wife by the discovery of his fault. Instead of being hurt "
                   "denying defending himself begging forgiveness instead of remaining "
                   "indifferent even anything would have been better than what he did "
                   "do his face utterly involuntarily reflex spinal action reflected "
                   "Stepan Arkadyevitch who was fond of physiology utterly involuntarily "
                   "assumed its habitual goodhumored and therefore idiotic smile."

                   "This idiotic smile he could not forgive himself. Catching sight of that "
                   "smile Dolly shuddered as though at physical pain broke out with her "
                   "characteristic heat into a flood of cruel words and rushed out of the "
                   "room. Since then she had refused to see her husband.";

    // Convert the text to lowercase
    for (auto &x : text) x = tolower(x);

    vector<vector<int>> adj(28, vector<int>(28));
    
    
    buildGraph(text, adj);
    
    vector<string> finalAns;
    bestFirstSearch(findIdx('e'), adj, finalAns);
    
   
    for (const auto &s : finalAns) {
        cout << s << endl;
    }

    return 0;
}
