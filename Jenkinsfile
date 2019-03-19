pipeline {
    agent { dockerfile true }
    environment {
        BUILD_OUTPUT = "project_build_binary.bin"
        TEST_OUTPUT = "test_binary.bin"
    }
    stages {
        stage('Initialization') {
            steps {
                sh """
                mkdir logs
                echo "Logs Initialized" >> logs/test.log
                """
            }
        }
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                make

                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh 'make run_tests >> logs/test.log' 
            }
        }
    }
    post {
        success {
            sh '''
            echo "All tests passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
        always {
            archiveArtifacts artifacts: "logs/*.log"
            sh '''
            ls
            echo "Starting clean"
            make clean
            rm -rf build/ logs/
            '''
        }
    }
}
