bash script

#!/bin/bash
echo "Enter the Number of Products: "
read N

# Loop through each product
for ((i=0; i<N; i++))
do
    echo "Enter the number of reviews for product $((i+1)): "
    read num
    sum=0
    avg=0

    # Loop through each review for the current product
    for ((j=0; j<num; j++))
    do
        echo "Enter The rating:"
        read rating

        # Skip if rating is less than 0
        if [ $rating -lt 0 ]
        then
            continue
        fi

        sum=$((sum+rating))
    done

    # Calculate average rating
    avg=$((sum/num))
    echo

    # Print rating category based on average rating
    if [ $avg -ge 90 ]
    then
        echo "Excellent"
        echo
    elif [ $avg -ge 80 ] && [ $avg -lt 90 ]
    then
        echo "Very Good"
        echo
    elif [ $avg -ge 70 ] && [ $avg -lt 80 ]
    then
        echo "Good"
        echo
    elif [ $avg -ge 60 ] && [ $avg -lt 70 ]
    then
        echo "Fair"
        echo
    elif [ $avg -ge 55 ] && [ $avg -lt 60 ]
    then
        echo "Bad"
        echo
    else
        echo "Poor"
        echo
    fi
done
