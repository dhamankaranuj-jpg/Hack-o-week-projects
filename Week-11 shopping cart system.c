#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* COLORS */
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

struct Item {
    int id;
    char name[50];
    int qty;
    float price;
};

/* PRODUCT MENU */
void showProducts() {
    printf(CYAN "\n🛍️ Available Products:\n" RESET);
    printf("1. Laptop       ₹55000\n");
    printf("2. Smartphone   ₹15000\n");
    printf("3. Headphones   ₹2000\n");
    printf("4. Shoes        ₹3000\n");
}

/* ADD ITEM */
void addItem() {
    FILE *fp = fopen("cart.txt", "a");
    struct Item it;
    int choice;

    showProducts();

    printf(YELLOW "\nEnter Product Choice: " RESET);
    scanf("%d", &choice);

    it.id = choice;

    switch(choice) {
        case 1: strcpy(it.name, "Laptop"); it.price = 55000; break;
        case 2: strcpy(it.name, "Smartphone"); it.price = 15000; break;
        case 3: strcpy(it.name, "Headphones"); it.price = 2000; break;
        case 4: strcpy(it.name, "Shoes"); it.price = 3000; break;
        default: printf(RED "Invalid choice!\n" RESET); return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &it.qty);

    fwrite(&it, sizeof(it), 1, fp);
    fclose(fp);

    printf(GREEN "\n✅ Item Added Successfully!\n" RESET);
}

/* VIEW CART */
void viewCart() {
    FILE *fp = fopen("cart.txt", "r");
    struct Item it;
    float total = 0;

    printf(CYAN "\n🛒 YOUR CART\n" RESET);

    while (fread(&it, sizeof(it), 1, fp)) {
        float cost = it.qty * it.price;
        printf("%s x%d = ₹%.2f\n", it.name, it.qty, cost);
        total += cost;
    }

    printf(YELLOW "\nTotal: ₹%.2f\n" RESET, total);
    fclose(fp);
}

/* REMOVE ITEM */
void removeItem() {
    FILE *fp = fopen("cart.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Item it;
    int id, found = 0;

    printf("Enter Product ID to remove: ");
    scanf("%d", &id);

    while (fread(&it, sizeof(it), 1, fp)) {
        if (it.id != id) {
            fwrite(&it, sizeof(it), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("cart.txt");
    rename("temp.txt", "cart.txt");

    if (found)
        printf(GREEN "Item removed!\n" RESET);
    else
        printf(RED "Item not found!\n" RESET);
}

/* BILL WITH GST + DISCOUNT */
void bill() {
    FILE *fp = fopen("cart.txt", "r");
    struct Item it;
    float total = 0;

    printf(CYAN "\n🧾 FINAL BILL\n" RESET);

    while (fread(&it, sizeof(it), 1, fp)) {
        float cost = it.qty * it.price;
        printf("%s x%d = ₹%.2f\n", it.name, it.qty, cost);
        total += cost;
    }

    float gst = total * 0.18;
    float discount = (total > 20000) ? total * 0.10 : 0;

    printf("\nSubtotal: ₹%.2f\n", total);
    printf("GST (18%%): ₹%.2f\n", gst);
    printf("Discount: ₹%.2f\n", discount);

    float final = total + gst - discount;

    printf(GREEN "Final Amount: ₹%.2f\n" RESET, final);
    printf("Thank You for Shopping! 😊\n");

    fclose(fp);
}

/* MAIN */
int main() {
    int choice;

    while (1) {
        printf(CYAN "\n\n🛒 ===== SMART SHOPPING CART =====\n" RESET);
        printf("1. Add Item\n");
        printf("2. View Cart\n");
        printf("3. Remove Item\n");
        printf("4. Generate Bill\n");
        printf("5. Exit\n");

        printf(YELLOW "Enter choice: " RESET);
        scanf("%d", &choice);

        switch(choice) {
            case 1: addItem(); break;
            case 2: viewCart(); break;
            case 3: removeItem(); break;
            case 4: bill(); break;
            case 5: exit(0);
            default: printf(RED "Invalid choice!\n" RESET);
        }
    }

    return 0;
}
