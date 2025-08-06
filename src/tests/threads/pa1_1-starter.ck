# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(pa1_1-starter) begin
(pa1_1-starter) Creating thread one.
number of threads: 2
thread with lowest priority: main
(pa1_1-starter) Increase priority.
(pa1_1-starter) Creating thread two.
number of threads: 3
thread with lowest priority: one
(pa1_1-starter) Decrease priority.
(pa1_1-starter) Creating thread three.
number of threads: 4
thread with lowest priority: two
(pa1_1-starter) end
EOF
pass;
