void duffs_device_expanded() {
    register short *to, *from;
    register unsigned count;
    {
        register unsigned n = (count + 7) / 8;
        switch (count % 8) {
            case 0: *to = *from++;
            case 7: *to = *from++;
            case 6: *to = *from++;
            case 5: *to = *from++;
            case 4: *to = *from++;
            case 3: *to = *from++;
            case 2: *to = *from++;
            case 1: *to = *from++;
        }
        while (--n > 0) {
            *to = *from++;
            *to = *from++;
            *to = *from++;
            *to = *from++;
            *to = *from++;
            *to = *from++;
            *to = *from++;
            *to = *from++;
        }
    }
}