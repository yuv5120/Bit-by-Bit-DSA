class Spreadsheet {
private:
    int rows;
    unordered_map<string, int> cells;
    
    int getOperand(const string &s) {
        if (isdigit(s[0])) 
            return stoi(s);
        return cells.count(s) ? cells[s] : 0;
    }
    
public:
    Spreadsheet(int rows) {
        this->rows = rows;
    }
    
    void setCell(string cell, int value) {
        cells[cell] = value;
    }
    
    void resetCell(string cell) {
        cells.erase(cell);
    }
    
    int getValue(string formula) {
        string f = formula.substr(1);
        size_t pos = f.find('+');
        string op1 = f.substr(0, pos);
        string op2 = f.substr(pos + 1);
        return getOperand(op1) + getOperand(op2);
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */