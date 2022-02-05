queue:
	gcc p1_mesq.c -o mesq1 ./mesq1
	gcc p2_mesq.c -o mesq2 ./mesq2

fifo:
	gcc p1_fifo.c -o fifo1 ./fifo1
	gcc p2_fifo.c -o fifo2 ./fifo2

socket:
	gcc p1_socket.c -o sock1 ./sock1
	gcc p2_socket.c -o sock2 ./sock2

run_q1:
	./mesq1

run_q2:
	./mesq2

run_f1:
	./fifo1

run_f2:
	./fifo2

run_s1:
	./sock1

run_s2:
	./sock2