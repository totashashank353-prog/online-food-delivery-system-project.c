#include <stdio.h>
#include <string.h>

// -------------------- MENU SYSTEM STRUCTURES --------------------
struct MenuItem {
    char name[50];
    int price;
};

struct MenuItem menuItems[] = {
    {"Pizza", 199},
    {"Burger", 99},
    {"Biryani", 249},
    {"Coke", 39}
};

int menuSize = 4;

struct CartItem {
    char name[50];
    int price;
    int quantity;
};

struct CartItem cart[20];
int cartCount = 0;

// -------------------- CART FUNCTIONS --------------------
int findItem(char item[]) {
    for (int i = 0; i < cartCount; i++) {
        if (strcmp(cart[i].name, item) == 0) {
            return i;
        }
    }
    return -1;
}

void addItemToCart(int itemIndex, int qty) {
    int index = findItem(menuItems[itemIndex].name);

    if (index != -1) {
        cart[index].quantity += qty;
    } else {
        strcpy(cart[cartCount].name, menuItems[itemIndex].name);
        cart[cartCount].price = menuItems[itemIndex].price;
        cart[cartCount].quantity = qty;
        cartCount++;
    }
    printf("\nItem added!\n");
}

void viewCart() {
    if (cartCount == 0) {
        printf("\nCart is empty\n");
        return;
    }

    printf("\n------ YOUR CART ------\n");
    for (int i = 0; i < cartCount; i++) {
        printf("%d. %s x%d = ₹%d\n",
            i + 1,
            cart[i].name,
            cart[i].quantity,
            cart[i].price * cart[i].quantity);
    }
}

void cancelItem() {
    viewCart();
    if (cartCount == 0) return;

    int num;
    printf("\nEnter item number to remove: ");
    scanf("%d", &num);

    if (num < 1 || num > cartCount) {
        printf("Invalid number\n");
        return;
    }

    for (int i = num - 1; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }
    cartCount--;

    printf("Item removed\n");
}

void checkout() {
    float total = 0;

    printf("\n--------- BILL ---------\n");

    for (int i = 0; i < cartCount; i++) {
        int itemTotal = cart[i].price * cart[i].quantity;
        printf("%s x%d = ₹%d\n", cart[i].name, cart[i].quantity, itemTotal);
        total += itemTotal;
    }

    float handling = 20;
    float delivery = 80;
    float gst = total * 0.05;

    float grandTotal = total + handling + delivery + gst;

    printf("\nItems Total       : ₹%.2f", total);
    printf("\nHandling Charges  : ₹%.2f", handling);
    printf("\nDelivery Charges  : ₹%.2f", delivery);
    printf("\nGST (5%%)          : ₹%.2f", gst);
    printf("\n-----------------------------");
    printf("\nGrand Total       : ₹%.2f\n", grandTotal);

    int c;
    printf("\n1. Order Now");
    printf("\n2. Exit to Menu");
    printf("\nEnter your choice: ");
    scanf("%d", &c);

    if (c == 1) {
        printf("\nYour order is successfully completed!\n");
        cartCount = 0;  // clear cart
    } else {
        printf("\nReturning to menu...\n");
    }
}

void menu() {
    int choice, qty;

    while (1) {
        printf("\n------ MENU ------\n");
        for (int i = 0; i < menuSize; i++) {
            printf("%d. %s - ₹%d\n", i + 1, menuItems[i].name, menuItems[i].price);
        }
        printf("5. View Cart\n");
        printf("6. Cancel Item\n");
        printf("7. Checkout\n");
        printf("8. Exit Program\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= menuSize) {
            printf("Enter quantity: ");
            scanf("%d", &qty);
            addItemToCart(choice - 1, qty);
        }
        else if (choice == 5) {
            viewCart();
        }
        else if (choice == 6) {
            cancelItem();
        }
        else if (choice == 7) {
            checkout();
        }
        else if (choice == 8) {
            printf("\nExiting program...\n");
            return;
        }
        else {
            printf("Invalid choice!\n");
        }
    }
}

// -------------------- MAIN PROGRAM --------------------
int main() {
    char regPhone[20], regEmail[50], regUser[50], regPass[50], regAddress[100];
    char loginEmail[50], loginPass[50];
    FILE *fp;
    int choice;

    printf("------ ONLINE FOOD ORDERING SYSTEM ------\n");

    printf("\n1. Register");
    printf("\n2. Login");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    // -------------------- REGISTRATION --------------------
    if (choice == 1) {
        printf("\n----- REGISTRATION -----\n");
        printf("Enter Phone Number: ");
        scanf("%s", regPhone);
        printf("Enter Email: ");
        scanf("%s", regEmail);
        printf("Enter Username: ");
        scanf("%s", regUser);
        printf("Enter Password: ");
        scanf("%s", regPass);
        printf("Enter Address: ");
        scanf(" %[^\n]s", regAddress);

        fp = fopen("user.txt", "w");
        if (fp == NULL) {
            printf("Error saving data!\n");
            return 1;
        }

        fprintf(fp, "%s\n%s\n%s\n%s\n%s\n",
                regPhone, regEmail, regUser, regPass, regAddress);
        fclose(fp);

        printf("\nRegistration Successful!\n");
    }

    // -------------------- LOGIN --------------------
    printf("\n----- LOGIN -----\n");
    printf("Enter Email: ");
    scanf("%s", loginEmail);
    printf("Enter Password: ");
    scanf("%s", loginPass);

    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        printf("\nNo users registered yet! Please register first.\n");
        return 1;
    }

    fscanf(fp, "%s %s %s %s %[^\n]", 
           regPhone, regEmail, regUser, regPass, regAddress);
    fclose(fp);

    if (strcmp(loginEmail, regEmail) == 0 && strcmp(loginPass, regPass) == 0) {
        printf("\nSuccessfully Logged In!\n");
        menu();
    } else {
        printf("\nLogin Failed! Email or Password Incorrect.\n");
    }

    return 0;
}