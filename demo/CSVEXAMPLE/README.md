This example demonstrates a query system reading from a file stream.

gen_feed.py creates the file stream by replacing its contents
every second, checking first if the GS-lite instance has finished
processing the file.

Additional features demonstrated:
  - a reference to an interface set in example.gsql
  - a reference to a library query in example2.gsql
  - the output_spec.cfg has query example putting output on a stream,
    while example2 periodically dumps output in files in directory output_dir
  - The files in output_dir are in gdat format.  Use gs-lite/bin/gdat2ascii
    to extract their contents to ascii
  - the runall script starts up query system, note the use of gsprintconsole
    for both example and example2
  - the killall script ensures that gsprintconsole and gen_feed.py instances
    are stopped.
