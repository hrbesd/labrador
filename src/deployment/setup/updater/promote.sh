STABLE=~/labrador/stable
UNSTABLE=~/labrador/unstable
DEV=~/labrador/dev

rm -r $STABLE
mv $UNSTABLE $STABLE
mv $DEV $UNStABLE
rm -r $DEV/*
