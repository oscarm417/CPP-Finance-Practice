#include <iostream>
#include <unordered_map>
#include "include/rapidcsv.h"
using namespace std;



class TradeSide { 
    public: 
        enum Side { BUY, SELL };
};

class Trade { 
    private: 
        string symbol;
        double price;
        int quantity;
        TradeSide::Side side;
    public:
        Trade(string symbol, double price, int quantity, TradeSide::Side side) {
            this -> symbol = symbol;
            this -> price = price;
            this -> quantity = quantity;
            this -> side = side;
        }
    
    void printTrade(){
        cout << "Symbol: " << symbol << ",";
        cout << "Price: " << price << ",";
        cout << "Quantity: " << quantity << ",";
        cout << "Side: " << side << endl;
    }
    string getSymbol() {
        return symbol;
    }

    int getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }
    TradeSide::Side getSide() { 
        return side;
    }
};

class TickerStats { 
    public:
        int totalBuyQuantity;
        int totalSellQuantity;
        int totalTradeValue;
        int lowestPrice;
        int highestPrice;

        TickerStats() {
            totalBuyQuantity = 0;
            totalSellQuantity = 0;
            totalTradeValue = 0;
            lowestPrice = INT_MAX;
            highestPrice = INT_MIN;
        }
    
    void updateStats(Trade trade) {
        if(trade.getSide() == TradeSide::BUY){
            totalBuyQuantity += trade.getQuantity();
        }
        else if(trade.getSide() == TradeSide::SELL){
            totalSellQuantity += trade.getQuantity();
        }

        totalTradeValue += trade.getPrice() * trade.getQuantity();

        if(trade.getPrice() < lowestPrice){
            lowestPrice = trade.getPrice();
        }
        if(trade.getPrice() > highestPrice){
            highestPrice = trade.getPrice();
        }
    }
};

int CalculateTickerStats(vector<Trade> trades) {
    unordered_map<string, TickerStats> tickerStatsMap;
    for(Trade currTrade: trades){
        tickerStatsMap[currTrade.getSymbol()].updateStats(currTrade);
    }
    for(auto tickerTradeStats: tickerStatsMap){
        cout << "_____________________________" << endl;
        cout << "Ticker: " << tickerTradeStats.first << endl;
        cout << "Total Buy Quantity: " << tickerTradeStats.second.totalBuyQuantity << endl;
        cout << "Total Sell Quantity: " << tickerTradeStats.second.totalSellQuantity << endl;
        cout << "Total Trade Value: " << tickerTradeStats.second.totalTradeValue << endl;
        cout << "Lowest Price: " << tickerTradeStats.second.lowestPrice << endl;
        cout << "Highest Price: " << tickerTradeStats.second.highestPrice << endl;
    }
    return 0;
};
        

int CalculatePortfolioStats(vector<Trade> trades) { 
    int totalBuyQuantity = 0;
    int totalSellQuantity = 0;
    int totalTradeValue = 0;
    int lowestPrice = INT_MAX;
    int highestPrice = INT_MIN;

    for(Trade currTrade: trades){
        if(currTrade.getSide() == TradeSide::BUY){
            totalBuyQuantity += currTrade.getQuantity();
        }
        else if(currTrade.getSide() == TradeSide::SELL){
            totalSellQuantity += currTrade.getQuantity();
        }

        totalTradeValue += currTrade.getPrice() * currTrade.getQuantity();

        if(currTrade.getPrice() < lowestPrice){
            lowestPrice = currTrade.getPrice();
        }
        if(currTrade.getPrice() > highestPrice){
            highestPrice = currTrade.getPrice();
        }
    }
    cout << "Total Buy Quantity: " << totalBuyQuantity << endl;
    cout << "Total Sell Quantity: " << totalSellQuantity << endl;
    cout << "Total Trade Value: " << totalTradeValue << endl;
    cout << "Lowest Price: " << lowestPrice << endl;
    cout << "Highest Price: " << highestPrice << endl;
    return 0;
};

vector<Trade> readTradesFromCSV(string filePath) {
    rapidcsv::Document doc(filePath);
    vector<Trade> trades;
    for(int i = 0; i < doc.GetRowCount(); i++){
        string symbol = doc.GetCell<string>(0,i);
        double price = doc.GetCell<double>(1,i);
        int quantity = doc.GetCell<int>(2,i);
        string sideStr = doc.GetCell<string>(3,i);
        TradeSide::Side side = (sideStr == "BUY") ? TradeSide::BUY : TradeSide::SELL;
        trades.push_back(Trade(symbol, price, quantity, side));
    }
    return trades;

}

int main() {
    // Symbol, Price, Quantity, Side
    vector<Trade> trades = readTradesFromCSV("trades.csv");
    cout << "=============================" << endl;
    CalculatePortfolioStats(trades);
    cout << "=============================" << endl;
    CalculateTickerStats(trades);
    return 0;
}


