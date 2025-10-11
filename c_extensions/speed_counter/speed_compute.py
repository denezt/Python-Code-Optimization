import speed_compute

val1 = 89
val2 = 43
calc = speed_compute.compute(val1, val2)
print("speed_compute.compute(%i, %i) = %i" % (val1, val2, calc))

for i in range(0,10):
    calc = speed_compute.fcompute(i)
    print("speed_compute.fcompute(%i) = %i" % (i, calc))
