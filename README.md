## Electronic Execution Algos

### Project Components
- Basket Trading
- TWAP
- VWAP
- Iceberg
- Participate
- Venue Simulation
- Synchronized Dark SOR
- Scraping SOR

## Notes on Basket Trading

Basket trading is a very simple concept. You want to trade multiple securities at the same time.
Perhaps it is a portfolio of mortgage REITs, and you want to increase or decrease your exposure in the same proportions
at the same time. You can work this very large aggregate of orders in waves, executing a percentage of the basket each time. A wave can be executed by through a subalgorithm or can be directly sent to the market via a SOR. When a wave is cancelled, all the pending orders in the wave
are cancelled. Multiple waves can be sent at the same time, although this defeats the purpose of wave trading.
In this project you create a basket wave by specifying the percentage, the lot and rounding configuration.

Aspects of Development: Validation, Cancellation/Replacement, Persistence, Execution Flexibility

## Notes on SOR

Situation: Want to route child orders to many different dark pools, minimizing transaction costs, market
impact, execution time. 

Problem #1: How do we know which dark pools to route our child orders to? Can
we develop a model to estimate the probability of a child order execution?

Problem#2: There are network and exchange latencies that present opportunities
for arbitrageurs who are able to pick up on the SOR routing behavior.  

In this project, I develop a model to account for past  and present latencies and adjust
dispatch time to achieve minimal difference in order arrival time across different exchanges. 
This is not the optimal solution to the arbitrage problem, as co-location of SORs is ultimately more reliable. 
For the execution probability model, I use Abdul Adhami's SOR paper which bases its calculation
on past and present participation and other liquidity indicators. 

### TODO

- Scraping SOR for lit venues (no dynamic reflect)
- Liquidity aggregator that allows the SOR to identify liquidity taking opportunities
- Toxicity analysis on venues

## Notes on Venue Simulation

The simulation of a continuous crossing auction was interesting. There are multiple data structures to represent an order book. 
Ultimately, I went with an AVL tree. Although it has good algorithmic performance, the performance is clearly not optimal
as I need to lock the tree every time an order triggers a tree modification. 

Research Notes:

https://pdfs.semanticscholar.org/be6a/9d7dfd3d4e95a7f7632f5c5181361bba5f8d.pdf

http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.190.3057

 http://qes.bmo.com/papers/17_BMO_SmartOrderRouters.pdf
