#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[50];
    char author[50];
};

void addBook() {
    FILE *fp = fopen("library.txt", "a");
    struct Book b;

    printf("\n📘 Enter Book ID: ");
    scanf("%d", &b.id);

    printf("📖 Enter Title: ");
    scanf(" %[^\n]", b.title);

    printf("✍️ Enter Author: ");
    scanf(" %[^\n]", b.author);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);

    printf("\n✅ Book Added Successfully!\n");
}

void displayBooks() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;

    printf("\n📚 --- Book List ---\n");

    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
        printf("-------------------------\n");
    }

    fclose(fp);
}

void searchBook() {
    FILE *fp = fopen("library.txt", "r");
    struct Book b;
    int id, found = 0;

    printf("\n🔍 Enter Book ID to search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\n✅ Book Found!\n");
            printf("Title: %s\nAuthor: %s\n", b.title, b.author);
            found = 1;
        }
    }

    if (!found)
        printf("\n❌ Book Not Found!\n");

    fclose(fp);
}

void deleteBook() {
    FILE *fp = fopen("library.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("\n🗑 Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id) {
            fwrite(&b, sizeof(b), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (found)
        printf("\n✅ Book Deleted Successfully!\n");
    else
        printf("\n❌ Book Not Found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n\n📚 ===== LIBRARY CATALOG =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: exit(0);
            default: printf("\n⚠️ Invalid Choice!\n");
        }
    }

    return 0;
}
