This example demonstrates a query system reading from a file stream.

gen_feed.py creates the file stream by replacing its contents
every second, checking first if the GS-lite instance has finished
processing the file.

The source file is in gdat format, use
  ../../bin/gdat2ascii example.gdat to see its contents

Additional features demonstrated:
  - a reference to an interface set in example.gsql
  - the runall script starts up query system, note the use of gsprintconsole
    to start processing
  - the killall script ensures that gsprintconsole and gen_feed.py instances
    are stopped.
