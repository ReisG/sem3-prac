# syntax <problem solution>

# LOG_PAR="$EJUDGE_LOGIN@$EJUDGE_SERVER_ADDRESS"

# # starting fuse
# ssh $LOG_PAR "mkdir ~/contest &&
#         /opt/ejudge/bin/ejudge-fuse --user $EJUDGE_LOGIN --password $EJUDGE_PASSWORD \
#         --url https://unicorn.ejudge.ru/cgi-bin/ ~/contest -o use_ino 2>/dev/null"

# # capturing contest id
# CONTEST_ID=$(ssh $LOG_PAR "ls ~/contest")

# echo $CONTEST_ID

# sending solution
scp $2 $EJUDGE_USER@$EJUDGE_SERVER:~/contest/543/problems/$1/submit/gcc
