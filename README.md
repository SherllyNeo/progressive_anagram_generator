# progressive_anagram_generator
A progressive anagram generator for mentalism in C.


## Usage:

```
./prog_ang jacob lizzy damien superman ironman cass dean sam


          1 -----> final result: lizzy
0 -----> words: [ jacob, lizzy, damien, superman, ironman, cass, dean, sam ] | ask: a
                              3 -----> final result: jacob
                    2 -----> words: [ jacob, cass, sam ] | ask: s
                                        4 -----> final result: sam
                              3 -----> words: [ cass, sam ] | ask: c
                                        4 -----> final result: cass
          1 -----> words: [ jacob, damien, superman, ironman, cass, dean, sam ] | ask: n
                              3 -----> final result: dean
                    2 -----> words: [ damien, superman, ironman, dean ] | ask: m
                                        4 -----> final result: superman
                              3 -----> words: [ damien, superman, ironman ] | ask: i
                                                  5 -----> final result: ironman
                                        4 -----> words: [ damien, ironman ] | ask: d
                                                  5 -----> final result: damien

You would ask at most 5 questions
```

### If not input is supplied, it will give an example
