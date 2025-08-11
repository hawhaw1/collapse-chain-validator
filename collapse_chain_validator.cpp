/*==========================================================

 Title:       Assignment 13 - Quantum Blockchain Forensics – Collapse Chain Validator
 Course:      CIS 2252
 Author:      <Hawraa Alzamel>
 Date:        < 08/ 08/2025 >
 Description: This program validates a chain of blocks by checking each 
 blocks hasg wh=hich computes a collapse bit from its data. It also apdates the Hash until the chain 
 is either verified or a mismatch is found.

 ==========================================================
*/

#include <iostream>
#include <vector>
using namespace std;

class Block {
private:
vector<double> quantumRow;
int declaredPrevHash;
Block* next;

int computeCollapse(const vector<double>& transform) const {
    double dot = 0.0;
    for (size_t i = 0; i < quantumRow.size(); ++i ) {
        dot += quantumRow[i] * transform[i];
    }
    return (dot * 1000.0 > 500.0) ? 1 : 0;
}
public:
    Block(const vector<double>& row, int prevHash)
    : quantumRow(row), declaredPrevHash(prevHash), next(nullptr) {}
    
    void setNext(Block* n ) {next = n; }
    Block* getNext() const {return next; }
    bool validate(int expectedPrevHash, const vector<double>& transform, int index) const {
        
        if (declaredPrevHash != expectedPrevHash) {
            cout << "Block " << index << ": Hash mismatch\n\n";
            cout << "CHAIN COMPROMISED - Integrity breach at block " << index << "\n";
            cout << "STATUS: Quantum-instability detected\n";
            return false;
        }
        cout << "Block " << index << ": Signature verified\n";
        
        int collapse = computeCollapse(transform);
        int nextExpectedHash = (collapse + expectedPrevHash) % 256;
        
        if (next != nullptr) {
            return next->validate(nextExpectedHash, transform, index + 1);
        }
        cout << "\nCHAIN VERIFIED - All blocks valid\n";
        cout << "STATUS: Quantum-stable\n";
        return true;
    }
};
class Blockchain {
private:
    Block* head;
    Block* tail;
    vector<double> transform;
    
public:
    explicit Blockchain(const vector<double>& t)
    : head(nullptr), tail(nullptr), transform(t) {}
    
    ~Blockchain() {
        for (Block* p = head; p; ) {
            Block* nxt = p->getNext();
            delete p;
            p = nxt;
        }
    }
    void addBlock(const vector<double>& row, int declaredPrevHash) {
        Block* b = new Block(row, declaredPrevHash);
        if (head == nullptr) {
            head = tail =b;
        } else {
            tail->setNext(b);
            tail = b;
        }
    }
    void validate() const {
        if (head == nullptr) {
            cout << "CHAIN VERIFIED - All blocks valid\n";
            cout << "STATUS: Quantum-stable\n";
            return;
        }
        head->validate(0, transform, 0);
    }
};

int main() {
ios:: sync_with_stdio(false);
cin.tie(nullptr);

int n;
if (!(cin >> n)) return 0;

vector<double> transform(n);
for (int i = 0; i < n; ++i) cin >> transform[i];

Blockchain chain(transform);
for (int bi = 0; bi < n; ++bi) {
    vector<double> row(n);
    for ( int j = 0; j < n; ++j) cin >> row[j];
    int declaredPrevHash; cin >> declaredPrevHash;
    chain.addBlock(row, declaredPrevHash);
}
    
    chain.validate(); // Begin validation process

    return 0;
}
