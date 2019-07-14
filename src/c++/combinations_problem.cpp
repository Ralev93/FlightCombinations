#include <bitset>
#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

#define MAX_BITSET_SIZE 64

void printBreakups(unordered_map<string, int> breakups) {
    unordered_map<string, int>::iterator itr;
    cout << "\tKEY\tELEMENT\n"; 
    for (itr = breakups.begin(); itr != breakups.end(); ++itr) { 
        cout << '\t' << itr->first 
             << '\t' << itr->second << '\n'; 
    } 
    cout << endl; 
}
 
list<list<bitset<MAX_BITSET_SIZE>>> get_computed_combinations(int n, 
    unordered_map<string, list<list<bitset<MAX_BITSET_SIZE>>>> combinations,
    bitset<MAX_BITSET_SIZE> alternative_ticket, 
    bitset<MAX_BITSET_SIZE> ticket)
    {
        string bits_key = alternative_ticket.to_string();
        list<bitset<MAX_BITSET_SIZE>> breakup;
        list<list<bitset<MAX_BITSET_SIZE>>> breakups;
        
        if (combinations.count(bits_key) > 0) {
            for (list<bitset<MAX_BITSET_SIZE>> old_breakups : combinations[bits_key]) {
               
                breakup.clear();
                breakup.push_front(ticket);
                
                for (bitset<MAX_BITSET_SIZE> old_ticket : old_breakups) {
                    breakup.push_front(old_ticket);
                }
                
                breakups.push_front(breakup);
            }
        }
        return breakups;
    }
 
list<list<bitset<MAX_BITSET_SIZE>>> findCombinations(int n, unordered_map<string, list<list<bitset<MAX_BITSET_SIZE>>>> combinations) {
    bitset<MAX_BITSET_SIZE> ticket;
    list<bitset<MAX_BITSET_SIZE>> breakup;
    list<list<bitset<MAX_BITSET_SIZE>>> breakups;
    int index = 0;
    
    for (int i=0; i < n; i++) {
        ticket.set(i, 1); // we start with ones!
    }
        
    while(index < n) {
        breakup.clear();
       
        ticket.flip(index);
        breakup.push_back(ticket);

	    bitset<MAX_BITSET_SIZE> alternative_ticket(ticket);
	    alternative_ticket.flip();
	    breakup.push_back(alternative_ticket);
	    
	    breakups.push_back(breakup);
	    list<list<bitset<MAX_BITSET_SIZE>>>
	        computed_combinations = get_computed_combinations(n, combinations,
	                                  alternative_ticket,
	                                  ticket);
	                                  
	    breakups.merge(computed_combinations);
	    
        index++;
        
    }
    
    return breakups; 
}

int main() {
	
    int n=5;
    unordered_map<string, list<list<bitset<MAX_BITSET_SIZE>>>> combinations; 
    bitset<MAX_BITSET_SIZE> key("11");
    
    for (int i=2; i <= n; i++){
        combinations[key.to_string()] = findCombinations(i, combinations);
        key.set(i, 1);
    }
    
    bitset<MAX_BITSET_SIZE> trivialBitset(key);
    list<bitset<MAX_BITSET_SIZE>> tmp;
    tmp.push_front(trivialBitset);
    combinations[key.to_string()].push_front(tmp); // push the all "1" bitset
    
    return 0;
}
