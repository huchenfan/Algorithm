#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

#undef UNICODE
#include <windows.h>

using namespace std;

struct  InvertTerm {
    InvertTerm(string docid, int frqes, int location)
        : docid_(std::move(docid))
        , frqes_(frqes)
    {
        locations_.emplace_back(location);
    }

    bool operator==(const InvertTerm& term) const
    {
        return docid_ == term.docid_;
    }

    bool operator<(const InvertTerm& term) const
    {
        return docid_ < term.docid_;
    }

    string docid_;  // 单词所在文档
    int frqes_;     // 单词出现的次数
    list<int> locations_;  // 单词出现的位置
};

// 倒排列表
class InvertList {
public:
    // 添加倒排项
    void addTerm(const string& docid, int location)
    {
        for(auto &term : termList_) {
            if(term.docid_ == docid) {
                term.frqes_++;
                term.locations_.emplace_back(location);
                return;
            }
        }
        termList_.emplace_back(docid, 1, location);
    }
    // 获取倒排列表内容(只读不写)
    const list<InvertTerm>& getInvertList() const
    {
        return  termList_;
    }
private:
    list<InvertTerm> termList_;
};

// 倒排索引
class InvertIndex {
public:
    void setSearchPath(const string& path)
    {
        cout << "搜索文件...";
        getAllFile(path.c_str());
        cout << "完成！！！" << endl;

        cout << "开始创建倒排索引";
        createInvertIndex();
        cout << "完成" << endl;
    }
    void setSuffix(string suffix)
    {
        suffix_ = suffix;
    }
    void query(string phrase)
    {
        // 先进行句子分词操作
        vector<string> wordList;
        char* word = strtok(const_cast<char*>(phrase.c_str()), " ");
        while(word != nullptr) {
            word = trim(word);
            if(strlen(word) > 0) {
                wordList.emplace_back(word);
            }
            word = strtok(nullptr, " ");
        }

        if(wordList.empty()) return;

        if(wordList.size() == 1) {
            auto it = invertMap_.find(wordList[0]);
            if(it == invertMap_.end()) {
                cout << "未搜索到任何匹配的内容！" << endl;
                return;
            }
            for(auto& term: it->second.getInvertList()) {
                cout << term.docid_  << " "<< "frqes:" << term.frqes_ << endl;
            }
        }
        else {
            vector<InvertList> invertList;
            for(int i = 0; i < wordList.size(); i++) {
                auto it = invertMap_.find(wordList[i]);
                if(it != invertMap_.end()) {
                    invertList.emplace_back(it->second);
                }
            }
            vector<InvertTerm> termShared;
            vector<InvertTerm> v1(invertList[0].getInvertList().begin(), invertList[0].getInvertList().end());
            for(int i = 1; i < invertList.size(); i++) {
                vector<InvertTerm> v2(invertList[i].getInvertList().begin(), invertList[i].getInvertList().end());
                sort(v1.begin(), v1.end());
                sort(v2.begin(), v2.end());
                set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(termShared));
                v1.swap(termShared);
                termShared.clear();
            }

            for(auto& term: v1) {
                cout << term.docid_  << " "<< "frqes:" << term.frqes_ << endl;
//                cout << "locations";
//                for(int pos : term.locations_) {
//                    cout << pos << " ";
//                }
            }
        }
    }
private:
    // 创建倒排索引
    void createInvertIndex()
    {
        for(string& filePath : fileList_) {
            cout << ".";
            FILE* pf = fopen(filePath.c_str(), "r");
            if(pf == nullptr) {
                cerr << filePath << ">>>> 打开失败！" << endl;
                continue;
            }
            vector<string> wordList;
            int location = 0;
            const int LINE_SIZE = 2048;
            char line[LINE_SIZE] = {0};
            while(!feof(pf)) {
                // 读一行文件内容
                fgets(line, LINE_SIZE, pf);
                char* word = strtok(line, " ");
                // 按照空格进行分词
                while(word != nullptr) {
                    word = trim(word);
                    if(strlen(word) > 0) {
                        wordList.emplace_back(word);
                    }
                    word = strtok(nullptr, " ");
                }
                for(string& w : wordList) {
                    location++;
                    auto it = invertMap_.find(w);
                    if(it == invertMap_.end()) {
                        InvertList list;
                        list.addTerm(filePath, location);
                        invertMap_.emplace(w, list);
                    }
                    else {
                        it->second.addTerm(filePath, location);
                    }
                }
            }
            fclose(pf);
        }
    }
    // 扫本地文件路径
    int getAllFile(const char* Path)
    {
        char szFind[MAX_PATH];
        WIN32_FIND_DATA FindFileData;
        strcpy(szFind, Path);
        strcat(szFind, "\\*.*");
        HANDLE hFind = FindFirstFile(szFind, &FindFileData);
        if(INVALID_HANDLE_VALUE == hFind) {
            return -1;
        }

        do
        {
            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
                    // 发现子目录，递归
                    char szFile[MAX_PATH] = {0};
                    strcpy(szFile, Path);
                    strcat(szFile, "\\");
                    strcat(szFile, FindFileData.cFileName);
                    getAllFile(szFile);
                }
            }
            else {
                // 找到文件， 处理
                string fileName(FindFileData.cFileName);
                int pos = fileName.find(suffix_);
                if(pos != string::npos && pos + suffix_.size() == fileName.size()) {
                    cout << Path << "\\" << FindFileData.cFileName << endl;
                    string filePath(Path);
                    filePath.append("\\");
                    filePath.append(fileName);
                    fileList_.emplace_back(filePath);
                }
            }
        } while (FindNextFile(hFind, &FindFileData));

        FindClose(hFind);
        return 0;
    }

    char* trim(char* word)
    {
        int i = 0;
        while(word[i] != '\0') {
            if(word[i] == ' ' || word[i] == '\t' || word[i] == '\n') {
                i++;
            }
            else {
                break;
            }
        }
        int j = i;
        while(word[j] != '\0') {
            if(word[j] == ' ' || word[j] == '\t' || word[j] == '\n') {
                break;
            }
            j++;
        }
        word[j] = '\0';
        return word + i;
    }
private:
    string suffix_;   // 过滤文档后缀
    list<string> fileList_;    // 存储所有需要建立倒排的文件
    unordered_map<string, InvertList> invertMap_;  // 词典 + 倒排列表
};

int main() {
    InvertIndex index;
    index.setSuffix(".cpp");
    index.setSearchPath("Algorithm_learn");
    while (true) {
        char buf[128] = {0};
        cout << "搜索内容：";
        cin.getline(buf, 128);
        index.query(buf);
    }

}
