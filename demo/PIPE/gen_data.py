import random
import time

ipv4s = ["1.2.3.4", "3.4.5.6", "112.221.54.34", "66.77.88.99"]
ipv6s = ["1234:4321:5678:8765:9abc:cba9:def0:0def",
	 "2234:4321:5678:8765:9abc:cba9:def0:0de2",
	"3234:4321:5678:8765:9abc:cba9:def0:0de3",
	"4234:4321:5678:8765:9abc:cba9:def0:0de4" ]

strings = ["foo", "bar", "zed", "flip", "flood"]
bools = ["TRUE", "FALSE"]

tstart = int(time.time())
tend = tstart+50
rec_per_ts = 5

for ts in xrange(tstart, tend+1):
	for rno in xrange(0, rec_per_ts):
		v2 = str(random.randint(1,100000))
		v3 = ipv4s[random.randrange(0,len(ipv4s))]
		v4 = ipv6s[random.randrange(0,len(ipv6s))]
		v5 = strings[random.randrange(0,len(strings))]
		v6 = bools[random.randrange(0,len(bools))]
		v7 = str(random.randint(1,100000))
		v8 = str(random.randint(1,100000))
		v9 = str(random.uniform(1,100000))
		rec = [str(ts), v2, v3, v4, v5, v6, v7, v8, v9]
		print ",".join(rec)

