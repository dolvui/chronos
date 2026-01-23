create X = 5 + 6;
create Y = X + 6;

print X;
print Y;

save STATE1;

save STATE2 [A+2];

choose X,Y;

retro STATE1;

undo 7;

undo 2 [A];

jmp 5;

create X = X + Y;

print X;
