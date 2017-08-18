#include <iostream>
#include "utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>
#include <ctime>

using namespace std;

struct publication {
    vector<string> tags;
    vector<double> embedding;
    vector<string> title;
};

struct publicationText {
    vector<string> tags;
    vector<string> title;
    string text;
};

struct methodScore {
    double topOne;
    double topFive;
    double averageRank;
};

static vector<publicationText> getPublicationsText(string fn) {
    ifstream inFile;
    inFile.open(fn);
    
    // DEFINE THE VECTOR OF PUBLICATIONS
    vector<publicationText> publications;

    if(inFile.is_open()) {
        string line;
        int lineNumber;
        while(inFile) {
            publicationText pub;
            getline(inFile, line);
            auto splitLine = stringSplit(line, "\t");
            pub.tags = stringSplit(splitLine[2], ",");
            pub.text = splitLine[4];
            pub.title.push_back(splitLine[1]);
            publications.push_back(pub);
        }
        inFile.close();
    } else {
        cout << "Cannot Open: " << fn << endl;
        exit(11);
    }
    return publications;
}

static vector<publication> getPublications(string fn) {
    ifstream inFile;
    inFile.open(fn);
    
    // DEFINE THE VECTOR OF PUBLICATIONS
    vector<publication> publications;

    if(inFile.is_open()) {
        string line;
        int lineNumber;
        while(inFile) {
            publication pub;
            getline(inFile, line);
            auto splitLine = stringSplit(line, "\t");
            pub.tags = stringSplit(splitLine[2], ",");
            auto splitVector = stringSplit(splitLine[4], ",");
            for(auto vec : splitVector) {
                try {
                    double asDouble = stod(vec);
                }
                catch (int e) {
                    cout << "Couldn't Convert: " << vec << endl;
                }
            }
            
            pub.embedding = stringSplitToDouble(splitLine[4], ",");
            pub.title.push_back(splitLine[1]);
            publications.push_back(pub);
        }
        inFile.close();
    } else {
        cout << "Cannot Open: " << fn << endl;
        exit(11);
    }
    return publications;
}

static map<string, vector<double>> getTestingVectors(string fn) {
    
    map<string, vector<double>> testingVectors;
    
    ifstream inFile;
    inFile.open(fn);

    if(inFile.is_open()) {
        string line;
        int lineNumber;
        while(inFile) {
            getline(inFile, line);
            auto splitted = stringSplit(line, "\t");
            auto text = splitted[0];
            auto splitVector = stringSplit(splitted[1], ",");
            vector<double> testVector;
            for(auto vec : splitVector) {
                try {
                    testVector.push_back(stod(vec));
                } catch(const std::invalid_argument&) {
                    break;
                }
            }
            if(testVector.size() > 0) {
                testingVectors[text] = testVector;
            }
        }
    } else{
        cout << "Cannot Open: " << fn << endl;
        exit(11);
    }
    return testingVectors;
}

static int calculateRank(vector<double> pubs, double similarity) {
    int rank = 1;
    for(auto pub : pubs) {
        if(pub > similarity) {
            rank++;
        }
    }
    return rank;
}

static vector<double> getRanks(map<string, vector<double>> testVectors, vector<publication> publications, bool tags, string modelName) {
    vector<double> ranks;
    
    int numberOfTests = 0;
    string typeTitle = tags ? "Tag" : "Title";
    cout << "Getting " << typeTitle << " Scores\n" << endl;
    for(int i=0; i<publications.size(); i++) {
        cout << (int)((double)i * 100) / (double)publications.size() << "%   \r" << flush;
        auto pub = publications[i];
        vector<string> queries;
        if(tags) {
            queries = pub.tags;
        } else{
            queries = pub.title;
        }
        vector<double> publicationVector = pub.embedding;
        for(auto query : queries) {
            if(testVectors.find(query) != testVectors.end()) {
                auto tagSimilarity = cosineSimilarity(testVectors[query], publicationVector);
            }
            else {
                break;
            }
            auto tagSimilarity = cosineSimilarity(publicationVector, testVectors[query]);
            vector<double> publicationSimilarities;
            for(auto pub : publications) {
                publicationSimilarities.push_back(cosineSimilarity(testVectors[query], pub.embedding));
            }
            auto rank = calculateRank(publicationSimilarities, tagSimilarity);
            ranks.push_back(rank);
            numberOfTests ++;
        }
    }
    cout << "100% Completed\n";
    return ranks;
}

static methodScore getScoreFromRankVector(vector<double> ranks, int nRanks) {
    methodScore score;

    double top1Val = nRanks * 0.01;
    double top5Val = nRanks * 0.05;
    double nTopFive;
    double nTopOne;
    double totalRank;

    for(auto rank : ranks) {
        totalRank += rank * 100 / nRanks;
        if(rank < top5Val) {
            nTopFive++;
            if(rank < top1Val) {
                nTopOne++;
            }
        }
    }

    score.averageRank = totalRank / nRanks;
    score.topOne = nTopOne * 100 / nRanks;
    score.topFive = nTopFive * 100 / nRanks;
    
    return score;
}

static string scoresToString(string methodName, string testingType, methodScore scores) {
    ostringstream scoresString;
    scoresString << methodName << "\n";
    scoresString << testingType << " Scores\n";
    scoresString << "Percentage in Top 1%: ";
    scoresString << scores.topOne;
    scoresString << "\nPercentage in Top 5%: ";
    scoresString << scores.topFive;
    scoresString << "\nAverage: ";
    scoresString << scores.averageRank;
    return scoresString.str();
}

static map<string, vector<string>> getTestingQueries(string fn) {
    ifstream inFile;
    inFile.open(fn);
    map<string, vector<string>> testingQueries;
    if(inFile.is_open()) {
        string line;
        while(inFile) {
            getline(inFile, line);
            string queryKey = stringSplit(line, ",")[0];
            vector<string> queries = stringSplit(line, ",");
            testingQueries[queryKey] = queries;
        }
    } else {
        cout << "Cannot Open: " << fn << endl;
        exit(11);
    }
    return testingQueries;
}

static int getWordCount(vector<string> queries, string text) {
    int frequency = 0;
    for(auto query : queries) {
        for (auto word : stringSplit(query, " ")) {
            if(text.find(word) != std::string::npos) {
                frequency += 1;
            }
        }
    }
    return frequency;
}

static int getQueryRank(int frequency, vector<int> allFrequencies) {
    int rank = 1;
    for(auto val : allFrequencies) {
        if(frequency < val) {
            rank += 1;
        }
    }
    return rank;
}

static vector<double> getWordFrequencyRanks(vector<publicationText> publications, map<string, vector<string>> queries, bool tags) {
    string output = tags ? "Getting Score for Tags" : "Getting Score for Titles";
    cout << output << "\n\n========================================\n" << endl;
    auto publicationsGlobal = publications;
    // Resized Publications for Testing
    auto publicationsLocal = publications;
    vector<double> queryRanks;
    int jj = 0;
    for(auto pubGlobal : publicationsGlobal) {
        jj += 1;
        // cout << (double)jj * 100 / (double)publications.size() << "% Completed              \r" << flush;
        cout << jj << " of " << publications.size() << " Completed.             \r" << flush;
        auto publicationQueries = tags ? pubGlobal.tags : pubGlobal.title;
        for(auto publicationQuery : publicationQueries) {
            vector<string> queryVector = queries[publicationQuery];
            queryVector.push_back(publicationQuery);
            vector<int> allFrequencies;
            auto tagFrequency = getWordCount(queryVector, pubGlobal.text);
            for(auto pubLocal : publicationsLocal) {
                auto wordCount = getWordCount(queryVector, pubLocal.text);
                allFrequencies.push_back(wordCount);
            }
            auto queryRank = getQueryRank(tagFrequency, allFrequencies);
            queryRanks.push_back(queryRank);
        }
    }
    cout << "100% Completed              \n";
    return queryRanks;
}

static void writeScoreString(vector<string> scores, string fn, string dir) {
    ofstream outFile;
    outFile.open(dir+fn);
    if(outFile.is_open()) {
        for(auto score : scores) {
            outFile << "===========================================================" << endl;
            outFile << score << endl;
        }
        outFile.close();
    } else{
        cout << "Couldn't Open File for Writing." << endl;
    }
}

int main() {

    string publicDataDir = "/Users/roberttimothyhoneybul/Desktop/academic-search/academicData/public-data/";
    string outDataDir = "/Users/roberttimothyhoneybul/Desktop/academic-search/academicData/scoring/cpp/results/";
    
    // Vector Similarity Measures
    vector<string> scoreOutputs;
    vector<string> modelNames = {"LDA_200", "D2V"};
    for(auto modelName : modelNames) {
        string publicationFilename = publicDataDir + modelName + "/txt/publications.txt";
        string tagFilename = publicDataDir + modelName + "/txt/tags.txt";
        string titleFilename = publicDataDir + modelName + "/txt/titles.txt";
        
        cout << "========================================\n" << endl;
        cout << "Scoring For: " << modelName << "\n" << endl;
        cout << "========================================\n" << endl;

        cout << "Reading Publications...     \r" << flush;
        auto publications = getPublications(publicationFilename);
        cout << "Reading Titles...            \r" << flush;
        auto titleVectors = getTestingVectors(titleFilename);
        cout << "Reading Tags...               \r" << flush;
        auto tagVectors = getTestingVectors(tagFilename);
        cout << "Data Loaded     \n\n========================================\n" << endl;
    
        auto tagRanks = getRanks(tagVectors, publications, true, modelName);
        auto tagScore = getScoreFromRankVector(tagRanks, publications.size());
        auto titleRanks = getRanks(titleVectors, publications, false, modelName);
        auto titleScore = getScoreFromRankVector(titleRanks, publications.size());
    
        scoreOutputs.push_back(scoresToString(modelName, "Tags", tagScore));
        scoreOutputs.push_back(scoresToString(modelName, "Titles", titleScore));
        
    }

    // Word Frequency Measures
    modelNames = {"WF"};
    for(auto modelName : modelNames) {
        cout << "========================================\n" << endl;
        cout << "Scoring: " << modelName << "\n" << endl;
        cout << "========================================\n" << endl;

        string publicationsFilename = publicDataDir + modelName + "/txt/publications.txt";
        string tagFilename = publicDataDir + modelName + "/txt/tags.txt";
        string titleFilename = publicDataDir + modelName + "/txt/titles.txt";

        cout << "Reading Publications...     \r" << flush;
        auto frequencyPublications = getPublicationsText(publicationsFilename);
        cout << "Reading Titles...            \r" << flush;
        map<string, vector<string>> frequencyTitles = getTestingQueries(titleFilename);
        cout << "Reading Tags...               \r" << flush;
        map<string, vector<string>> frequencyTags = getTestingQueries(tagFilename);

        auto frequencyTitleRanks = getWordFrequencyRanks(frequencyPublications, frequencyTitles, false);
        auto frequencyTitleScores = getScoreFromRankVector(frequencyTitleRanks, frequencyPublications.size());

        auto frequencyTagRanks = getWordFrequencyRanks(frequencyPublications, frequencyTags, true);
        auto frequencyTagScores = getScoreFromRankVector(frequencyTagRanks, frequencyPublications.size());

        scoreOutputs.push_back(scoresToString(modelName, "Tags", frequencyTagScores));
        // scoreOutputs.push_back(scoresToString(modelName, "Titles", frequencyTitleScores));

    }

    writeScoreString(scoreOutputs, "scores.txt", outDataDir);

}
