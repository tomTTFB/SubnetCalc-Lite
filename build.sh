gcc -Os -s \
    -fno-asynchronous-unwind-tables -fcf-protection=none -fno-stack-protector \
    -no-pie \
    -Wl,--gc-sections \
    -Wl,-z,noseparate-code \
    -Wl,-z,norelro \
    -Wl,-z,nodynamic-undefined-weak \
    -Wl,--build-id=none \
    -Wl,--no-eh-frame-hdr \
    -o subnetcalc main.c

strip -R .comment -R .note.gnu.property -R .note.ABI-tag -R .eh_frame subnetcalc

wc -c subnetcalc