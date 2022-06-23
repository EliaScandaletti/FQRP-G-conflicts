#!/usr/bin/sh

cd src;

make;

./progs/exh_filt_gen_main 1 15 > ~/exh_filt_gen.out 2> ~/exh_filt_gen.err &

./progs/exh_gen_main 1 15 > ~/exh_gen.out 2> ~/exh_gen.err &

./progs/int_filt_gen_main 1 50 100000000 > ~/int_filt_gen.out 2> ~/int_filt_gen.err &

{ ./progs/rand_filt_gen_main 1 15 100000000 && ./progs/rand_filt_log_main 16 50 100000000; } > ~/rand_filt_gen.out 2> ~/rand_filt_gen.err &
