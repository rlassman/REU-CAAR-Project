Compile: make
Run: 
    2-path: ./radixSort -r <number of rounds> -c -n <input size> -s <seed>
    cycle: ./radixSort_cycle ...

-c checks that the input is correctly sorted

Tested with uniform input generation (Elizabeth's old version), up to 2 bil inputs, 3 rounds (computes average runtime), seeds 42, 41, & 40

To do:
    - change implementation to use parlay sequence instead of arrays (can't run on inputs bigger than 2 bil currently)
    - benchmark with different input types
    - may want to redo uniform distribution so every alg uses the same uniform distribution generator
        - also the parlay algs benchmarking threw out the first run (some of the inputs had a significantly higher runtime for the first round for region sort)

